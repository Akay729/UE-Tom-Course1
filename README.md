# ActionRougelike
### (Si ho fatto un errore di battitura)

Progetto di studio basato su [Tom Looman - Unreal Engine 5 C++ Developer]

## Obiettivo

Riprendere le basi di Unreal Engine C++ e costruire gradualmente un action/rougelike, seguendo le best practice del motore (componenti, delegate, GameplayTags, data-oriented design, GAS-like systems, ect).

## Progresso

- [x] 1. Introduction & Setup
- [x] 2. Project Start (C++ class, ActorComponents, Input Move/Look)
- [x] 3. Collision & Physics — (Input & Spawning)
- [x] 4. Assignment 1  
- [x] 5. Interfaces & Collision Queries **in corso**
- [ ] 6. Blueprint Scripting
- [ ] 7. Assignment 2
- [ ] 8. Player Attributes
- [ ] 9. Improving The Systems
- [ ] 10. Assignment 3
- [ ] 11. Enemy Monsters (AI / Behavior Tree / EQS)
- [ ] 12. Assignment 4
- [ ] 13. Action System (GAS-like)
- [ ] 14. GameplayTags
- [ ] 15. Attributes
- [ ] 16. Assignment 5
- [ ] 17. Debugging & Polish
- [ ] 18. Data-Oriented Design
- [ ] 19. Buffs & Debuffs
- [ ] 20. Assignment 6
- [ ] 21. Enemy Spawn System
- [ ] 22. Enemy AI Continued
- [ ] 23. Assignment 7
- [ ] 24. UMG (User Interfaces)

## Setup

- **Engine:** Unreal Engine 5.6.1
- **OS:** Linux
- **IDE:** VS Code (C/C++ extension) / JetBrains Rider

### Note o punti chiave che ho scontrato durante il progetto
- meglio non usare rider su linux non ho capito il motivo ma mi fa crashare ogni versione di UE dopo la 5.5.2, ho capito soltato che anche passare ad un elemento della hud del edito causa il crash istantaneo.
- In Assignment 1: Ho capito la importanza di UNiagaraFunctionLibrary::SpawnSystemAttached e diUNiagaraFunctionLibrary::SpawnSystemAtLocation 
