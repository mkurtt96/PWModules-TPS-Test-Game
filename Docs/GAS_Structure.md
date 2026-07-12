# GAS Structure — ProjectWTps & PW Modules

Architecture overview of the Gameplay Ability System (GAS) stack in this project, spanning the game module and the git submodules **PWGAS**, **PWAbility**, and **PWCoreLibs** (plus the optional **PWTeams**).

> Submodule paths: `Plugins/PWGAS`, `Plugins/PWAbility`, `Plugins/PWCoreLibs`, `Plugins/PWTeams` (see `.gitmodules`).

---

## 1. Module & submodule dependency map

Arrows point from a module to what it depends on (from each `*.Build.cs`). The dashed `PWGasCore → PWAbility` link is the key decoupling: `PWAbilityModule_Actor` spawns any actor class that implements `IPWSpellParamsInterface` (enforced via `MustImplement`), so PWGasCore never links against PWAbility — the actors are wired in through data assets.

```mermaid
flowchart TB
    subgraph GameRepo["🎮 PWModules-TPS-Test-Game — game repo"]
        ProjectWTps["<b>ProjectWTps</b> — game module<br/>TPSPlayerState · ProjectWTpsCharacter<br/>AttributeSet_Core · AttributeSet_Vitals<br/>TPSHUD · Combat AI"]
    end

    subgraph SubPWGAS["📦 Plugins/PWGAS — submodule"]
        PWGasCore["<b>PWGasCore</b> — Runtime<br/>PWAbilitySystemComponent<br/>PWModularGameplayAbility + Modules<br/>Targeting · Precast · AbilityTasks"]
        PWGASCoreEditor["<b>PWGASCoreEditor</b> — Editor<br/>ability detail customization"]
        PWAttributes["<b>PWAttributes</b> — Runtime<br/>PWAttributeSetBase<br/>PWAttributeSet_Tagged"]
        GMR["<b>GameplayMessageRouter</b><br/>GameplayMessageSubsystem<br/>Runtime + BP nodes"]
    end

    subgraph SubPWAbility["📦 Plugins/PWAbility — submodule"]
        PWAbility["<b>PWAbility</b> — Runtime<br/>WBaseSpellActor · BaseProjectile<br/>SplineMovementProjectile<br/>PrecastDecal · MyEffectActor"]
    end

    subgraph SubPWCoreLibs["📦 Plugins/PWCoreLibs — submodule"]
        PWSharedTypes["<b>PWSharedTypes</b><br/>SpellParams + Extensions<br/>MultiDataArray"]
        PWContracts["<b>PWContracts</b><br/>IAffectable · IEffectReceiver<br/>IPWSpellParamsInterface"]
        PWInput["<b>PWInput</b><br/>PWInputRouter · PWInputConfig<br/>PWEnhancedInputComponent"]
        PWLogging["<b>PWLogging</b><br/>DebugLog · LogChannels"]
        PWFoundation["<b>PWFoundation</b><br/>WTM timer utilities"]
    end

    subgraph Engine["⚙️ Unreal Engine plugins"]
        UEGAS["GameplayAbilities<br/>GameplayTags · GameplayTasks"]
        UEEnhancedInput["EnhancedInput"]
        UENiagara["Niagara"]
    end

    PWTeams["📦 Plugins/PWTeams — submodule"]

    ProjectWTps --> PWGasCore
    ProjectWTps --> PWAttributes
    ProjectWTps --> PWContracts
    ProjectWTps --> PWInput
    ProjectWTps --> PWLogging
    ProjectWTps --> UEGAS
    ProjectWTps --> UEEnhancedInput

    PWGASCoreEditor --> PWGasCore
    PWGasCore --> PWSharedTypes
    PWGasCore --> PWContracts
    PWGasCore --> GMR
    PWGasCore --> UEGAS
    PWGasCore --> UENiagara
    PWAttributes --> UEGAS

    PWGasCore -. "spawns spell actors via<br/>IPWSpellParamsInterface — data-driven,<br/>no compile-time dependency" .-> PWAbility

    PWAbility --> PWSharedTypes
    PWAbility --> PWContracts
    PWAbility --> UENiagara
    PWAbility -. "optional · WITH_PWTEAMS" .-> PWTeams

    PWContracts --> PWSharedTypes
    PWSharedTypes --> UEGAS
    PWInput --> UEEnhancedInput
    PWInput -->|"GameplayTags"| UEGAS
    GMR -->|"GameplayTags"| UEGAS
```

Layering summary:

| Layer | Modules | Role |
|---|---|---|
| Game | `ProjectWTps` | Owns the ASC (on `TPSPlayerState`), concrete attribute sets, characters, AI, UI |
| GAS framework | `PWGasCore`, `PWGASCoreEditor`, `PWAttributes`, `GameplayMessageRouter` | ASC extension, modular ability framework, attribute base classes, decoupled messaging |
| Ability actors | `PWAbility` | Spawnable spell/projectile actors consumed by PWGasCore's action modules |
| Core libs | `PWSharedTypes`, `PWContracts`, `PWInput`, `PWLogging`, `PWFoundation` | Shared types, interfaces (contracts), input routing, logging, utilities |

---

## 2. Core GAS class diagram

Inheritance, interfaces, and ownership across the modules. `ATPSPlayerState` owns the `UPWAbilitySystemComponent` and both attribute sets; the character resolves the ASC through `IAbilitySystemInterface`.

```mermaid
classDiagram
    direction TB

    %% ── Engine ──
    class UAbilitySystemComponent { <<Engine>> }
    class UGameplayAbility { <<Engine>> }
    class UAttributeSet { <<Engine>> }

    %% ── PWGasCore ──
    class UPWAbilitySystemComponent {
        <<PWGasCore>>
        FPWASC_AbilityLifecycle
        FPWASC_EffectLifecycle
        FPWASC_CooldownHandler
        FPWASC_InputBinding
        FPWASC_DataManagement
        FPWASC_VfxLifecycle
    }
    class UPWGameplayAbilityBase { <<PWGasCore>> }
    class UPWModularGameplayAbility {
        <<PWGasCore>>
        +TArray~UPWAbilityModule~ Modules
    }
    class UPWGameplayAbility_Instant { <<PWGasCore>> }
    class UPWGameplayAbility_Channeling { <<PWGasCore>> }
    class UPWGameplayAbility_Charged { <<PWGasCore>> }
    class UPWGameplayAbility_Confirmed { <<PWGasCore>> }
    class UPWGameplayAbility_Passive { <<PWGasCore>> }
    class UAbilityDataAsset { <<PWGasCore>> }
    class UPWAbilityRegistry { <<PWGasCore>> }

    %% ── PWAttributes ──
    class UPWAttributeSetBase { <<PWAttributes>> }

    %% ── PWCoreLibs ──
    class USpellParams { <<PWSharedTypes>> }
    class USpellParamsExtension { <<PWSharedTypes>> }
    class IAffectable { <<PWContracts>> }
    class IEffectReceiver { <<PWContracts>> }
    class IPWSpellParamsInterface { <<PWContracts>> }

    %% ── PWAbility ──
    class AWBaseSpellActor { <<PWAbility>> }
    class ABaseProjectile { <<PWAbility>> }
    class ASplineMovementProjectile { <<PWAbility>> }
    class IProjectile { <<PWAbility>> }

    %% ── Game ──
    class ATPSPlayerState { <<ProjectWTps>> }
    class AProjectWTpsCharacter { <<ProjectWTps>> }
    class UAttributeSet_Core { <<ProjectWTps>> }
    class UAttributeSet_Vitals { <<ProjectWTps>> }

    %% ASC
    UAbilitySystemComponent <|-- UPWAbilitySystemComponent

    %% Abilities
    UGameplayAbility <|-- UPWGameplayAbilityBase
    UPWGameplayAbilityBase <|-- UPWModularGameplayAbility
    UPWModularGameplayAbility <|-- UPWGameplayAbility_Instant
    UPWModularGameplayAbility <|-- UPWGameplayAbility_Channeling
    UPWModularGameplayAbility <|-- UPWGameplayAbility_Charged
    UPWModularGameplayAbility <|-- UPWGameplayAbility_Confirmed
    UPWModularGameplayAbility <|-- UPWGameplayAbility_Passive

    %% Data
    UPWAbilityRegistry o-- UAbilityDataAsset : registers
    UPWAbilitySystemComponent --> UAbilityDataAsset : grants from

    %% Attributes
    UAttributeSet <|-- UPWAttributeSetBase
    UPWAttributeSetBase <|-- UAttributeSet_Core
    UPWAttributeSetBase <|-- UAttributeSet_Vitals

    %% Game ownership
    ATPSPlayerState *-- UPWAbilitySystemComponent : owns ASC
    ATPSPlayerState *-- UAttributeSet_Core
    ATPSPlayerState *-- UAttributeSet_Vitals
    ATPSPlayerState ..|> IAffectable
    ATPSPlayerState ..|> IEffectReceiver
    AProjectWTpsCharacter ..|> IEffectReceiver
    AProjectWTpsCharacter --> UPWAbilitySystemComponent : GetASC()

    %% Spell actors
    AWBaseSpellActor ..|> IPWSpellParamsInterface
    AWBaseSpellActor <|-- ABaseProjectile
    ABaseProjectile ..|> IProjectile
    ABaseProjectile <|-- ASplineMovementProjectile
    AWBaseSpellActor --> USpellParams : receives
    USpellParams o-- USpellParamsExtension : extensions
```

Also in `PWAttributes`: `UPWAttributeSet_Tagged` (a second `UAttributeSet` base) and an experimental per-attribute-set family (`BasicAttribute` / `ClampedAttribute` / `RegeneratingAttribute`, `AS_Health`, `AS_MovementSpeed`) that is currently commented out.

---

## 3. Modular ability system (PWGasCore)

`UPWModularGameplayAbility` is composed of `UPWAbilityModule` objects in three categories. PWGasCore extends `USpellParamsExtension` (from PWSharedTypes) with Actor/Projectile/Effect extensions to hand spawn data to the spell actors.

```mermaid
flowchart LR
    MGA["UPWModularGameplayAbility"] -- "composed of" --> M["UPWAbilityModule"]

    M --> AM["<b>UPWActionModule</b><br/>executes the ability's effect"]
    M --> CM["<b>UPWControlModule</b><br/>drives activation flow"]
    M --> DM["<b>UPWDataModule</b><br/>provides values"]

    AM --> ModActor["Actor"]
    ModActor --> ModMultiActor["MultiActor"]
    ModActor --> ModProjectile["Projectile"]
    ModProjectile --> ModMultiProjectile["MultiProjectile"]
    AM --> ModAura["Aura"]
    AM --> ModInstantEffect["InstantEffect"]

    CM --> ModTargeting["Targeting"]
    CM --> ModPrecast["Precast"]
    CM --> ModNiagara["Niagara"]

    DM --> ModEffect["Effect"]
    DM --> ModRange["Range"]
    DM --> ModRadius["Radius"]
```

Supporting systems in PWGasCore:

- **ASC composition** — `UPWAbilitySystemComponent` delegates to handler classes: `FPWASC_AbilityLifecycle`, `FPWASC_EffectLifecycle`, `FPWASC_CooldownHandler`, `FPWASC_InputBinding`, `FPWASC_DataManagement`, `FPWASC_VfxLifecycle`.
- **Targeting** — `PWTargetPolicyBase` + presetup policies (`CursorSingleTargeting`, `CursorAOETargeting`, `ScreenCenterTargeting`, `SingleTargetResolver`, `SphereTargetResolver`, `ClampRangeFromPawn`).
- **Precast** — `PWPrecastControllerComponent` + visualizers (`CircleDecalVisualizer`, `ProjectilePathVisualizer`); `PWAbility` supplies the `PrecastDecal` actor.
- **Ability tasks** — `TargetDataUnderMouse`, `AbilityTask_WaitInputEvent`, `AbilityTask_PlayMontageAddTagAndWait`, `PWAbilityTask_TargetFromSource`, cooldown-change async tasks.
- **Effects** — `PWGameplayEffectContext`, `PWExecCalc_Base`, `GASCoreTags`.
