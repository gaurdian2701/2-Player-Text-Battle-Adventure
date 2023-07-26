#include <iostream>
#include <cstdlib>
#include <memory>

template <typename T>

class Player
{

protected:
    std::string playerID;
    std::string playerType;
    int health;
    int baseDamage;
    int lowerAdditionalDamageLimit;
    int upperAdditionalDamageLimit;
    int lowerHealLimit;
    int upperHealLimit;
    int randomNumber;

public:
    bool specialActivated = false;

public:
    bool dealtStun = false;

    bool isAlive = true;

public:
    Player(std::string pID, std::string pType, int hp, int dps, int LADL, int UADL, int LHL, int UHL) : playerID(pID), playerType(pType), health(hp), baseDamage(dps), lowerAdditionalDamageLimit(LADL),
                                                                                                        upperAdditionalDamageLimit(UADL), lowerHealLimit(LHL), upperHealLimit(UHL)
    {
        health = hp;
        baseDamage = dps;
        playerType = pType;
        playerID = pID;
    }

public:
    virtual ~Player() {}

public:
    std::string GetPlayerID()
    {
        return playerID + ": ";
    }

public:
    std::string GetPlayerType()
    {
        return playerType;
    }

public:
    int GetHealth()
    {
        return health;
    }

public:
    int GetBaseDamage()
    {
        return baseDamage;
    }

public:
    int GetLowerAdditionalDamage()
    {
        return lowerAdditionalDamageLimit;
    }

public:
    int GetUpperAdditionalDamage()
    {
        return upperAdditionalDamageLimit;
    }

public:
    int GetLowerHealLimit()
    {
        return lowerHealLimit;
    }

public:
    int GetUpperHealLimit()
    {
        return upperHealLimit;
    }

public:
    bool aliveCheck()
    {
        return isAlive;
    }

public:
    virtual void TakeDamage(T val) {}

public:
    virtual void Heal() {}

public:
    virtual int Attack() {}

public:
    virtual void ActivateSpecialAbility() {}

public:
    virtual void ActivatePassiveAbility() {}
};

class Knight : public Player<int>
{
    int additionalDamage;
    int healAmount;
    int currentHealth = GetHealth();

public:
    Knight(std::string playerID, std::string playerType, int health, int baseDamage, int LADL, int UADL, int LHL, int UHL) : Player(playerID, playerType, health, baseDamage, LADL, UADL, LHL, UHL)
    {
        std::cout << "\"I wish you well. I am a Knight of the Golden Age. I shall fight till I draw my last breath.\"\n\n";
    }

public:
    ~Knight()
    {
        std::cout << GetPlayerID() << "The Knight has been laid to rest!\n\n";
    }

public:
    int Attack() override
    {
        std::cout << GetPlayerID() << "\n\n";

        additionalDamage = rand() % (GetUpperAdditionalDamage() - GetLowerAdditionalDamage() + 1) + GetLowerAdditionalDamage();
        std::cout << "The " << GetPlayerType() << " has dealt " << GetBaseDamage() + additionalDamage << " damage!\n\n";
        return GetBaseDamage() + additionalDamage;
    }

public:
    void Heal() override
    {
        std::cout << GetPlayerID() << "\n\n";

        if (currentHealth == health)
        {
            std::cout << "The " << GetPlayerType() << "'s health is already full!\n";
            return;
        }

        healAmount = rand() % (GetUpperHealLimit() - GetLowerHealLimit() + 1) + GetLowerHealLimit();
        std::cout << GetPlayerType() << " has healed by " << healAmount << " health points!\n";

        currentHealth += healAmount;

        if (currentHealth + healAmount >= health)
            currentHealth = health;

        std::cout << "Current Health of the " << GetPlayerType() << " is " << currentHealth << "\n\n";
    }

public:
    void TakeDamage(int val) override
    {
        std::cout << GetPlayerID() << "\n\n";

        randomNumber = rand() % 3;

        if (specialActivated)
        {
            std::cout << GetPlayerType() << " has taken zero damage!\n\n";
            specialActivated = false;
            return;
        }

        val -= (25.0 / 100.0) * (val);
        std::cout << "As a part of the " << GetPlayerType() << "'s Passive Ability, there is a 25% reduction in incoming damage!\n\n";

        if (currentHealth - val <= 0)
        {
            std::cout << "The " << GetPlayerType() << " has taken fatal damage!\n"
                      << "He has died!\n\n";
            currentHealth = 0;
            isAlive = false;
            return;
        }

        currentHealth -= val;

        std::cout << "The " << GetPlayerType() << " has taken damage of " << val << "!\n"
                  << "Remaining health is: " << currentHealth << "\n\n";

        if (currentHealth <= health / 2 && randomNumber == 0)
        {
            ActivateSpecialAbility(2);
            return;
        }

        if (currentHealth <= health / 4 && randomNumber == 1)
        {
            ActivateSpecialAbility();
            return;
        }
    }

    void ActivateSpecialAbility(int amount)
    {
        std::cout << "Special Ability Activated:  Increased Base Damage\n\n";
        baseDamage += amount;
    }

public:
    void ActivateSpecialAbility() override
    {
        std::cout << "Special Ability Activated:  Invulnerable to next attack\n\n";
        specialActivated = true;
    }
};

class Sorcerer : public Player<int>
{
    int additionalDamage;
    int healAmount;
    int currentHealth = GetHealth();
    bool reviveActive;

public:
    Sorcerer(std::string playerID, std::string playerType, int health, int baseDamage, int LADL, int UADL, int LHL, int UHL) : Player(playerID, playerType, health, baseDamage, LADL, UADL, LHL, UHL)
    {
        std::cout << " \"Greetings. I am a Sorcerer of old. My wand shall be your sword and shield.\" \n";
    }

public:
    ~Sorcerer()
    {
        std::cout << GetPlayerID() << "The Sorcerer has been laid to rest!\n\n";
    }

public:
    void Heal() override
    {
        std::cout << GetPlayerID() << "\n\n";

        dealtStun = false;

        if (currentHealth == health)
        {
            std::cout << "The " << GetPlayerType() << "'s health is already full!\n";
            return;
        }

        healAmount = rand() % (GetUpperHealLimit() - GetLowerHealLimit() + 1) + GetLowerHealLimit() + 5;

        currentHealth += healAmount;

        std::cout << GetPlayerType() << " has healed by " << healAmount << " health points!\n";
        std::cout << "As a part of the " << GetPlayerType() << "'s Passive, he heals by 3 extra points!\n";

        if (currentHealth + healAmount >= health)
            currentHealth = health;

        std::cout << "Current Health of the " << GetPlayerType() << " is " << currentHealth << ".\n\n";
    }

public:
    int Attack() override
    {
        std::cout << GetPlayerID() << "\n\n";

        dealtStun = false;
        additionalDamage = rand() % (GetUpperAdditionalDamage() - GetLowerAdditionalDamage() + 1) + GetLowerAdditionalDamage();
        std::cout << "The " << GetPlayerType() << " has dealt " << GetBaseDamage() + additionalDamage << " damage!\n\n";
        randomNumber = rand() % 7;
        if (randomNumber == 3)
            ActivatePassiveAbility();

        return GetBaseDamage() + additionalDamage;
    }

public:
    void TakeDamage(int val) override
    {
        std::cout << GetPlayerID() << "\n\n";

        if (currentHealth - val <= 0)
        {
            if (!specialActivated)
            {
                ActivateSpecialAbility();
                return;
            }

            std::cout << "The " << GetPlayerType() << " has taken fatal damage!\n"
                      << "He has died!\n\n";
            currentHealth = 0;
            isAlive = false;
            return;
        }

        currentHealth -= val;

        std::cout << "The " << GetPlayerType() << " has taken damage of " << val << "!\n"
                  << "Remaining health of the " << GetPlayerType() << " is " << currentHealth << "\n\n";
    }

public:
    void ActivateSpecialAbility() override
    {

        std::cout << "Sorcerer's special ability: Revive Activated!\n\n";
        specialActivated = true;
        currentHealth = (50.0 / 100.0) * health;
    }

public:
    void ActivatePassiveAbility() override
    {
        std::cout << "Sorcerer's Passive ability: Stun Activated!\n\n";
        dealtStun = true;
    }
};

class Barbarian : public Player<int>
{
    int additionalDamage;
    int healAmount;
    int currentHealth = GetHealth();
    int specialCounter = 0;
    int randomNumber;

public:
    Barbarian(std::string playerID, std::string playerType, int health, int baseDamage, int LADL, int UADL, int LHL, int UHL) : Player(playerID, playerType, health, baseDamage, LADL, UADL, LHL, UHL)
    {
        std::cout << " \"AAAAAAAAA!. JUST LET ME KILL ALREADY! I WANT MORE BLOOOOOOOOOD!\" \n";
    }

public:
    ~Barbarian()
    {
        std::cout << GetPlayerID() << "The Barbarian has been laid to rest!\n\n";
    }

public:
    int Attack() override
    {
        std::cout << GetPlayerID() << "\n\n";

        randomNumber = rand() % 4;

        if (specialActivated)
        {
            specialActivated = false;
            baseDamage -= 10;
        }

        if (randomNumber == 2)
            ActivatePassiveAbility();

        if (specialCounter == 4)
            ActivateSpecialAbility();

        additionalDamage = rand() % (GetUpperAdditionalDamage() - GetLowerAdditionalDamage() + 1) + GetLowerAdditionalDamage();
        std::cout << "The " << GetPlayerType() << " has dealt " << GetBaseDamage() + additionalDamage << " damage!\n\n";
        specialCounter++;
        return GetBaseDamage() + additionalDamage;
    }

public:
    void Heal() override
    {
        std::cout << GetPlayerID() << "\n\n";

        if (currentHealth == health)
        {
            std::cout << "The " << GetPlayerType() << "'s health is already full!\n";
            return;
        }

        healAmount = rand() % (GetUpperHealLimit() - GetLowerHealLimit() + 1) + GetLowerHealLimit();
        std::cout << GetPlayerType() << " has healed by " << healAmount << " health points!\n";

        currentHealth += healAmount;

        if (currentHealth + healAmount >= health)
            currentHealth = health;

        std::cout << "Current Health of the " << GetPlayerType() << " is " << currentHealth << "\n\n";
    }

public:
    void TakeDamage(int val) override
    {
        std::cout << GetPlayerID() << "\n\n";

        if (currentHealth - val <= 0)
        {
            std::cout << "The " << GetPlayerType() << " has taken fatal damage!\n"
                      << "He has died!\n\n";
            currentHealth = 0;
            isAlive = false;
            return;
        }

        currentHealth -= val;

        std::cout << "The " << GetPlayerType() << " has taken damage of " << val << "!\n"
                  << "Remaining health of the " << GetPlayerType() << " is " << currentHealth << "\n\n";
    }

public:
    void ActivateSpecialAbility() override
    {
        std::cout << "Barbarian's Special Ability: Rage Attack Activated!\n";
        baseDamage += 10;
        specialActivated = true;
    }

public:
    void ActivatePassiveAbility() override
    {
        std::cout << "Barbarian's Passive Ability: Attack Heal Activated!\n"
                  << "The Barbarian has healed by 5 health points!\n";

        if (currentHealth + 5 <= health)
            currentHealth += 5;

        std::cout << "Current Health of the Barbarian is: " << currentHealth << "\n\n";
    }
};

class GameManager
{
public:
    void PrintInfo()
    {

        std::cout << "---WELCOME TO THE 2 PLAYER BATTLE ADVENTURE!---\n\n";

        std::cout << "You get to choose between two classes.\n"
                  << "Press 1 ---> Knight\n"
                  << "Press 2 ---> Sorcerer\n"
                  << "Press 3 ---> Barbarian\n\n";

        std::cout << "---DETAILS---\n\n";

        std::cout << "------KNIGHT------\n\n";

        std::cout << "The Knight deals moderate damage, but specializes in defense.\n\n";

        std::cout << "Health:  100\n";
        std::cout << "Base Damage:  10\n";
        std::cout << "Additional Damage:  "
                  << "3-6\n";
        std::cout << "Healing Range:  "
                  << "2-4\n";
        std::cout << "Passive Ability:  "
                  << "Damage reduction by 25%\n";
        std::cout << "Special Ability 1(Activated at 50% health or below):  "
                  << "Permanently increase Base Damage by 1(33% chance)\n";
        std::cout << "Special Ability 2:(Activated at 25% health or below)  "
                  << "Zero Damage taken during the next turn(33% percent chance)\n\n";

        std::cout << "------SORCERER------\n\n";
        std::cout << "The Sorcerer deals high damage with spells and specializes in healing and stunning.\n"
                  << "He has low health.\n\n";

        std::cout << "Health:  80\n";
        std::cout << "Base Damage:  12\n";
        std::cout << "Additional Damage:  "
                  << "2-4 \n";
        std::cout << "Healing Range:  "
                  << "4-6 \n";
        std::cout << "Passive Ability 1:  "
                  << "Can Heal additional 5 points with every heal\n";
        std::cout << "Passive Ability 2: "
                  << "15% chance during every attack to stun the enemy, causing them to not play during the next round.\n";
        std::cout << "Special Ability (Activated at death -> ONCE ONLY):  "
                  << "Sorcerer gets revived at 50% health\n\n";

        std::cout << "------BARBARIAN------\n\n";
        std::cout << "The Barbarian deals very high damage using sheer brute force, absolutely demolishing anyone in front of him.\n"
                  << "However, he heals very poorly and has low health.\n";

        std::cout << "Health: 75\n";
        std::cout << "Base Damage: 15\n";
        std::cout << "Additional Damage: "
                  << "1-4\n";
        std::cout << "Healing Range: "
                  << "2-5 \n";
        std::cout << "Passive Ability: 25% chance to heal 5 points on every attack\n";
        std::cout << "Special Ability: If the Barbarian decides to attack for four turns consecutively, he will go into a "
                  << "bloodthirsty rage with the ability to deal massive damage on his next attack.\n\n";
    }

    bool MakeChoice(Player<int> *&p, std::string id)
    {
        int choice;
        bool check;

        enum playerType
        {

            K = 1,
            S = 2,
            B = 3
        };

        std::cin >> choice;

        if (!(choice >= K && choice <= B))
        {
            std::cout << "You have entered an invalid value. Please enter 1, 2, or 3\n\n";
            std::cin.clear();
            std::cin.ignore(256, '\n');
            return false;
        }

        switch (choice)
        {

        case K:
            std::cout << "You have chosen the Knight class.\n";
            p = new Knight(id, "Knight", 100, 8, 4, 6, 2, 4);

            check = true;
            break;

        case S:
            std::cout << "You have chosen the Sorcerer class.\n";
            p = new Sorcerer(id, "Sorcerer", 80, 12, 2, 4, 4, 6);
            check = true;
            break;

        case B:
            std::cout << "You have chosen the Barbarian class.\n";
            p = new Barbarian(id, "Barbarian", 70, 15, 1, 4, 2, 5);
            check = true;
            break;

        default:
            std::cout << "Choose again.\n";
            check = false;
            break;
        }

        return check;
    }

public:
    void PlayGame()
    {
        Player<int> *p1 = nullptr;
        Player<int> *p2 = nullptr;

        bool check = false;

        while (check == false)
        {
            std::cout << "Player 1, choose your class.\n";
            check = MakeChoice(p1, "P1");
        }

        std::unique_ptr<Player<int>> player1(p1);

        check = false;

        while (check == false)
        {
            std::cout << "Player 2, choose your class.\n";
            check = MakeChoice(p2, "P2");
        }

        std::unique_ptr<Player<int>> player2(p2);

        std::cout << "Let us start the battle! Player 1 goes first.\n\n";

        while (player1->aliveCheck() && player2->aliveCheck())
        {

            std::string turnChoice;

            std::cout << "\nPLAYER 1's TURN:\n\n";

            if (player2->dealtStun)
                std::cout << "Player 1 has been stunned, so their turn has been skipped.\n";

            else if (!(player1->aliveCheck()))
                break;

            else
            {
                std::cout << "Player 1, enter 1 to attack, enter anything else to heal.\n";
                std::cin >> turnChoice;
                std::cout << "-------------------------------------\n";

                if (turnChoice == "1" && !(player2->dealtStun))
                    player2->TakeDamage(player1->Attack());

                else
                    player1->Heal();
                
                std::cout << "-------------------------------------\n";
            }

            std::cout << "\nPLAYER 2's TURN:\n\n";

            if (player1->dealtStun)
                std::cout << "Player 2 has been stunned, so their turn has been skipped.\n";

            else if (!(player2->aliveCheck()))
                break;

            else
            {
                std::cout << "Player 2, enter 1 to attack, enter anything else to heal.\n";
                std::cin >> turnChoice;
                std::cout << "-------------------------------------\n";
                if (turnChoice == "1" && !(player1->dealtStun))
                    player1->TakeDamage(player2->Attack());

                else if (!(player1->dealtStun))
                    player2->Heal();

                std::cout << "-------------------------------------\n";
            }
        }

        if (p1->aliveCheck())
            std::cout << "Player 1: " << player1->GetPlayerType() << " is the winner!\n\n";
        else
            std::cout << "Player 2: " << player2->GetPlayerType() << " is the winner!\n\n";
    }
};

int main()
{
    GameManager manager;

    manager.PrintInfo();
    manager.PlayGame();

    return 0;
}
