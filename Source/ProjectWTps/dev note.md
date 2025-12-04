general attribute changes like health change 
        should be broadcasted with dynamic delegate, get referenced and listened by the classes that requires updates
event based changes should use Gameplay Message Subsystem
        event such as ability cooldowns, or character death, ui purchases, etc.
abilities with inputs are activated through ASC input press function via TryActivateAbility
        
abilities that auto activates - my current system or passive abilities uses gameplay tags, add "Ability.Activation.OnGranted" and "Ability.Deactivation.OnRemoved"
        however these are handled in ASC via tryactivate to avoid double activation, But i assume if we assign a tag for abilities, they can also use gameplayevents,
            to be looked into.

---

