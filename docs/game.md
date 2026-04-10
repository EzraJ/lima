# Legend
AA - Auto Attack
AE - Ability Exponent
APT - Attacks Per Turn
HP - Health Points
MR - Magic Resist
# TUI/2D turn based MOBA game
## Elevator Pitch
LIMA(name tbd) is a MOBA inspired heavily by LOL, DOTA2, D&D, and YOMI. Instead of being a real time game, players will be given a certain amount of time(i.e 15s/30s) to select an ability or movement action to take during a turn. LIMA will be tile/hexagon based. There is zero RNG in any game of LIMA. The map is a 3 level layered arena, and each layer has different win conditions. The map changes depending on which layer gets completed first. Completing the win condition on 2 layers results in a win. 

## Elements of A Turn
The beginning of a round will start off with "per-round" interactions like HP regen.

Each player will be given a certain amount of time to choose a spell, autoattack, or movement to take for their turn. Each action taken will have a cast time that determines where in the order they go.   

For example, in a round with two players; Player A uses a spell with a cast value of 100, and Player B uses a movement action with a cast value of 200. When the round starts, Player A's spell gets casted before player B can move.  
Each spell, movement, and autoattack will have their own base cast values that additionally scale with a players set of attributes.  
The intention is to have 2 teams with 6 players for a 6v6. 

TBD if you can use all three of AA, Move, and Ability cast, with downside of combining all cast times together.

## (Basic) Design of Characters
For now, 9 character types will exist. The primary design can either be Tank, Damage, or Healer. The secondary design can either be Tank, Damage, or Healer.  
The Tank archetype will interact with incoming damage. The Damage archetype will interact with outgoing damage. The Healer archetype will interact with healing.  
For example, a Tank/Tank will be a character fully designed about tanking damage for the team with minimal focus on outgoing damage, and would be a Consitution character.  
A character like this would have an aura that redirects incoming damage towards themselves instead of their teammates.  
A Tank/Damage will be a character designed around turning incoming damage into outgoing damage, and would be a Strength character.   
A Tank/Healer will be a character designed around turning incoming damage into outgoing healing, and would be an Intelligence character. 

# Character Design
Characters will have each attribute from D&D, and base stats that are more specific. Additionally, characters will have a primary attribute that dictates how much damage their auto attacks deal, and if they do Magic Damage, Physical Damage, True Damage, or a mix. Every stat has a growth stat attached to it. Max character level TBD. Each character will have no limit on minimum/maximum ability counts or passives, but every character will have atleast one passive. Abilities and Passives can scale from any stat. Ability Exponent will take any number in an ability/passive and apply an exponent(i.e. an AE of 1.5 will take every number and apply an exponent of 1.5) Maximum AE, APT, and AA Ratio TBD.  
Abilities and Passives can scale off of base stats and attributes. 

## Auto Attacking
Auto attacks are a very powerful tool in a turn based game with spells. They are inherently a spell that does not fail to land, as a result they are scaled with an AA Ratio, and multiplied by an Attacks Per Turn stat. Additionally, Attacks Per Turn round down, and can round down to 0 damage if they have less than 1 APT. 

## Base Stats(Plus per level gains)
- Level
- XP
- HP
- HP Regen
- Mana
- Mana Regen
- Armor
- Magic Resist
- AA Ratio
- APT
- AE
- Cast Reduction %
- Movement Speed(Movement Cast Time Reduction and total distance)
- Attributes
    - Strength
    - Dexterity
    - Constitution
    - Intelligence
    - Wisdom
    - Charisma

## Strength(Physical Damage)
HP, HP Regen
## Dexterity(Physical Damage)
AA Ratio, Armor, and Cast Reduction %
## Constitution(True Damage)
HP, MR, and Armor
## Intelligence(Magic Damage)
Mana Regen and AE
## Wisdom(Magic Damage)
Mana 
## Charisma(33/33/33 Physical/Magic Damage/True Damage)
A Little bit of every stat. 

# Map Design 
The map will consist of three different layers with three different win conditions. To win a game a team must have 2/3 of the win conditions met. The map will change and have different effects depending on which layer is won first. 

## Top Layer
TBD

## Middle Layer
The middle layer will be setup like a traditional MOBA; three different lanes and a jungle. Each lane has minions pushing against multiple towers that all eventually protect a central entity. Defeating the enemys central entity is the win condition. The jungle and corners will have various entrances that allow travel to either the bottom or top layer(but not at the same time). Minions and towers give gold and XP.  


## Bottom Layer
TBD 