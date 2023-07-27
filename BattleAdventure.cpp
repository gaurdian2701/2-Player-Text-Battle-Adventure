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
    int additionalDamage;
    int currentHealth;

public:
    bool specialActivated = false;

public:
    bool dealtStun = false;

    bool isAlive = true;

public:
    Player(std::string pID) : playerID(pID)
    {
        playerID = pID;
    }

public:
    virtual ~Player() {}

    std::string GetPlayerID()
    {
        return playerID + ": ";
    }

    std::string GetPlayerType()
    {
        return playerType;
    }

    int GetHealth()
    {
        return health;
    }

    int GetBaseDamage()
    {
        return baseDamage;
    }

    int GetLowerAdditionalDamage()
    {
        return lowerAdditionalDamageLimit;
    }

    int GetUpperAdditionalDamage()
    {
        return upperAdditionalDamageLimit;
    }

    int GetLowerHealLimit()
    {
        return lowerHealLimit;
    }

    int GetUpperHealLimit()
    {
        return upperHealLimit;
    }

    bool aliveCheck()
    {
        return isAlive;
    }

    virtual void TakeDamage(T val) {}

    virtual void Heal() {}

    virtual int Attack() {}

    virtual void ActivateSpecialAbility() {}

    virtual void ActivatePassiveAbility() {}
};

class Knight : public Player<int>
{

public:
    Knight(std::string playerID) : Player(playerID)
    {
        std::cout << "\"I wish you well. I am a Knight of the Golden Age. I shall fight till I draw my last breath.\"\n\n";
        playerType = "Knight";
        health = 100;
        baseDamage = 8;
        lowerAdditionalDamageLimit = 4;
        upperAdditionalDamageLimit = 6;
        lowerHealLimit = 2;
        upperHealLimit = 4;
        currentHealth = health;
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
        int healAmount;

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
    bool reviveActive;

public:
    Sorcerer(std::string playerID) : Player(playerID)
    {
        std::cout << " \"Greetings. I am a Sorcerer of old. My wand shall be your sword and shield.\" \n";
        playerType = "Sorcerer";
        health = 80;
        baseDamage = 12;
        lowerAdditionalDamageLimit = 2;
        upperAdditionalDamageLimit = 4;
        lowerHealLimit = 4;
        upperHealLimit = 6;
        currentHealth = health;
    }

public:
    ~Sorcerer()
    {
        std::cout << GetPlayerID() << "The Sorcerer has been laid to rest!\n\n";
    }

public:
    void Heal() override
    {
        int healAmount;
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
    int specialCounter = 0;

public:
    Barbarian(std::string playerID) : Player(playerID)
    {
        std::cout << " \"AAAAAAAAA!. JUST LET ME KILL ALREADY! I WANT MORE BLOOOOOOOOOD!\" \n";
        currentHealth = health;
        health = 70;
        baseDamage = 15;
        lowerAdditionalDamageLimit = 1;
        upperAdditionalDamageLimit = 4;
        lowerHealLimit = 2;
        upperHealLimit = 5;
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
        int healAmount;

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
            p = new Knight(id);

            check = true;
            break;

        case S:
            std::cout << "You have chosen the Sorcerer class.\n";
            p = new Sorcerer(id);
            check = true;
            break;

        case B:
            std::cout << "You have chosen the Barbarian class.\n";
            p = new Barbarian(id);
            check = true;
            break;

        default:
            std::cout << "Choose again.\n";
            check = false;
            break;
        }

        return check;
    }

    void GetPlayerInput(Player<int> *&p, std::string id)
    {
        bool check = false;

        while (check == false)
        {
            std::cout << id << ", choose your class.\n";
            check = MakeChoice(p, id);
        }
    }

    void InitiateCombat(std::unique_ptr<Player<int>> &player1, std::unique_ptr<Player<int>> &player2)
    {
        while (player1->aliveCheck() && player2->aliveCheck())
        {

            std::string turnChoice;

            if (player2->dealtStun)
                std::cout << "Player 1 has been stunned, so their turn has been skipped.\n";

            else if (!(player1->aliveCheck()))
                break;

            else
            {
                std::cout << "\nPLAYER 1's TURN:\n\n";
                std::cout << "Player 1, enter 1 to attack, enter anything else to heal.\n";
                std::cin >> turnChoice;
                PrintBorder();

                if (turnChoice == "1" && !(player2->dealtStun))
                    player2->TakeDamage(player1->Attack());

                else
                    player1->Heal();

                PrintBorder();
            }

            if (player1->dealtStun)
                std::cout << "Player 2 has been stunned, so their turn has been skipped.\n";

            else if (!(player2->aliveCheck()))
                break;

            else
            {
                std::cout << "\nPLAYER 2's TURN:\n\n";

                std::cout << "Player 2, enter 1 to attack, enter anything else to heal.\n";
                std::cin >> turnChoice;
                PrintBorder();
                if (turnChoice == "1" && !(player1->dealtStun))
                    player1->TakeDamage(player2->Attack());

                else if (!(player1->dealtStun))
                    player2->Heal();

                PrintBorder();
            }
        }
    }

    void DecideWinner(std::unique_ptr<Player<int>> &player1, std::unique_ptr<Player<int>> &player2)
    {
        if (player1->aliveCheck())
            std::cout << "Player 1: " << player1->GetPlayerType() << " is the winner!\n\n";
        else
            std::cout << "Player 2: " << player2->GetPlayerType() << " is the winner!\n\n";
    }

    inline void PrintBorder()
    {
        std::cout << "-------------------------------------\n";
    }

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

    void PlayGame()
    {
        Player<int> *p1 = nullptr;
        Player<int> *p2 = nullptr;

        GetPlayerInput(p1, "P1");
        GetPlayerInput(p2, "P2");

        std::unique_ptr<Player<int>> player1(p1);
        std::unique_ptr<Player<int>> player2(p2);

        std::cout << "Let us start the battle! Player 1 goes first.\n\n";

        InitiateCombat(player1, player2);
        DecideWinner(player1, player2);
    }
};

int main()
{
    GameManager manager;

    manager.PrintInfo();
    manager.PlayGame();

    return 0;
}
