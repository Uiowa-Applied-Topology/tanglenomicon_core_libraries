Design documentation for the tanglenomicon project.


```mermaid
erDiagram
    Runner ||--|{ Generator : Runs
    Runner ||--|{ Invariant : Runs
    Runner ||--|{ Translator : Runs
		Generator ||--||Notation : Uses
		Invariant ||--||Notation : Uses
		Translator ||--|{ Notation : ""
		Generator ||--||Storage : Uses
		Invariant||--||Storage : Uses
		Translator ||--|| Storage : Uses


```