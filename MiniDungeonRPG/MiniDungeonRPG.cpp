/** Assignment **/
/* Simple RPG dungeon Game */


#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <array>
#include <ctime>    // for the time()
#include <cstdlib>  // for system(), srand(), rand(), and exit()
#include <conio.h>  // for the getch()
#include <fstream>  // for file handling
#include <cstring>  // for strncpy


using namespace std;

// generate the seed for the random number, to make sure every time program run will have different random output
int seed = time(0);


void Welcome_to_the_Game()
{
            cout << "******************************************************\n"
                    << "**      ##### #   # ##### #### #### ##### #####     **\n"
                    << "**      #   # #   # #   # #    #    #   # #   #     **\n"
                    << "**      #   # #   # #   # # ## #### #   # #   #     **\n"
                    << "**      #   # #   # #   # #  # #    #   # #   #     **\n"
                    << "**      ##### ##### #   # #### #### ##### #   #     **\n"
                    << "**                                                  **\n"
                    << "**                                                  **\n"
                    << "**\t\tPress any key to START\t\t    **\n"
                    << "**                                                  **\n"
                    << "**                                                  **\n"
                    << "******************************************************\n";
}

void Introduction()
{
        cout << "Welcome to the Dungeon! \n"
                << "A century ago, world changed. Without warning, a Dungeons, known as \"Nemesis\",\n"
                << "erupted across the land. \n "
                << endl
                << "Nemesis twisting the landscape and unleashing monstrous\n"
                << "creatures that come from other dimensions.... \n"
                <<endl
                << "The fragile peace that once existed between the Kingdom, Empire, Tribes shattered. \n"
                <<  "Every forces try to claimed and control Nemesis. \n"
                << "Since it not only brings fear, it come with opportunities, \n"
                <<  "people found treasures, weapons, elixirs, and ancient magic scroll from it.\n"
                <<endl
                << "Through wars and negotiations, each forces finally reached an agreement, \n"
                << "Adventure Guild raised to achieve mutual checks and balances....\n"
                << "and the one who monitors the dungeon. \n"
                << endl
                << "You, as a wanderer, joining the guild and expect to find your opportunities in Nemesis...... "
                <<endl
                <<endl;

}

// --------------------------------------- Global variable-------------------------------------------------------------//
string character_name;
int character_age, character_class_choice , starting_floor =1;

bool player_raise_shield = 0, enemy_raise_shield = 0;
bool game_state, game_complete = 0, loadstate =0;
// --------------------------------------- Global variable -------------------------------------------------------------//

// ------------------------------------------------ Character building function -------------------------------------------------------------//
void character_building()
{
        cout << "Please enter your name (in one word): ";
        cin >> character_name;
        cout << "Please enter your age (number only): ";
        cin >> character_age;
        cout << "Choose your Class: \n"
                << "1. Paladin\t[ Sword & Shield ]\n"
                << "2. Warrior\t[ Great Sword ] \n"
                << "3. Ranger\t[ Dagger & Bow ]\n"
                << "4. Wizard\t[ Wand ]" << endl;
        cin >> character_class_choice;
}
// ------------------------------------------------ End of Character building function ----------------------------------------------------------//

//--------------------------------------------------------- Here is the status class-----------------------------------------------------------------//
class Status
{
    private:
       int HP;
       int SP;
       int Attack_a;
       int base_a;
       int crit_a;
       int Attack_b;
       int base_b;
       int crit_b;
       int Shield;
       bool Poison;     // currently not using
       bool Fear;         // currently not using

    public:
        void set_HP(int damage, int heal);
        int get_HP()
        {
            return HP;
        }

        void set_SP(int counter1, int counter2);
        int get_SP()
        {
            return SP;
        }

        // Define the attack interval of the character
        void set_base_a_crit_a(int base , int crit);
        void set_base_b_crit_b(int base, int crit);

        int get_base_a()   { return base_a; }
        int get_crit_a()    {return crit_a;}
        int get_base_b()    {return base_b;}
        int get_crit_b()    {return crit_b;}


        int set_Attack_a();
        int get_Attack_a()
        {
            return Attack_a;
        }

        int set_Attack_b();
        int get_Attack_b()
        {
            return Attack_b;
        }

        void set_Shield(int defense);
        int get_Shield()
        {
            return Shield;
        }

        void poisoned();
        void Feared();

        void reset_status(int hp, int sp, int base_a, int crit_a, int base_b, int crit_b, int shield);

        // a constructor helps to initialize status, we use 'poison' to initialize both poison and fear section
        // because it is 0 for sure at the begining
        Status(int hp, int sp, int base_a, int crit_a, int base_b, int crit_b, int shield, bool poison) :
            HP(hp),
            SP(sp),
            base_a(base_a),
            crit_a(crit_a),
            base_b(base_b),
            crit_b(crit_b),
            Shield(shield),
            Poison(poison),
            Fear(poison)
            {}

};

// Initialize the Player status (Declaring first)
            Status Player(0,0,0,0,0,0,0,0);

// Initializing the enemy (Declaring first)
            Status Goblin          (40, 3, 2, 4, 3, 5, 0, 0);
            Status Beast            (50, 3, 3, 5, 4, 6, 0, 0);
            Status Explorer       (50, 3, 3, 4, 4, 7, 1, 0);
            Status Monster        (60, 3, 3, 5, 4, 8, 1, 0);
            Status Demon_Nemesis    (110, 3, 5, 6, 6, 8, 4, 0);


// 0--------------------  below is the function from the Status class ----------------------------0 //

// Setting the HP and SP
void Status::set_HP(int damage, int heal)
{
        HP = HP - damage + heal;
}
void Status::set_SP(int counter1, int counter2)
{
    // maximum SP only can be 4
        if (SP>=0 && SP <4)
        SP = SP - counter1 + counter2;
        if (SP == 4)
        SP = SP - counter1;
}

// Set the attack range of an unit
void Status::set_base_a_crit_a(int base, int crit)
{
        base_a = base;
        crit_a = crit;
}
void Status::set_base_b_crit_b(int base, int crit)
{
        base_b = base;
        crit_b = crit;
}
// Generate the attack value
int Status::set_Attack_a()
{
        // method of simulate the attack value range
        return     rand() % (crit_a - base_a +1) + base_a;
}
int Status::set_Attack_b()
{
        // method of simulate the attack value range
        return      rand() % (crit_b - base_b +1) + base_b;
}

//Set the Defense value ( only player will this )
void Status::set_Shield(int defense)
{
        Shield = defense + 5;
}

void Status::reset_status(int hp, int sp, int base_a_reset, int crit_a_reset, int base_b_reset, int crit_b_reset, int shield_reset)
{
            HP = hp;
            SP = sp;
            base_a = base_a_reset;
            crit_a = crit_a_reset;
            base_b = base_b_reset;
            crit_b = crit_b_reset;
            Shield = shield_reset;

}
// ----------------------------------------------------------- end of Status class ------------------------------------------------------------------//

// ----------------------------------------------------------- Save Game Function ------------------------------------------------------------------//
    // Function to save game state
bool SaveGame(int current_floor) {
    // Create/open save file as a text file
    ofstream save_file("game_save.txt");

    if (!save_file) {
        cout << "Error: Could not create save file!" << endl;
        return false;
    }

    // Write data to file in a readable text format
    save_file << character_name << endl;
    save_file << character_age << endl;
    save_file << character_class_choice << endl;
    save_file << current_floor << endl;
    save_file << Player.get_HP() << endl;
    save_file << Player.get_SP() << endl;
    save_file << Player.get_Shield() << endl;
    save_file << Player.get_base_a() << endl;
    save_file << Player.get_crit_a() << endl;
    save_file << Player.get_base_b() << endl;
    save_file << Player.get_crit_b() << endl;

    save_file.close();

    cout << "Game saved successfully!" << endl;
    return true;
}

// ----------------------------------------------------------- Save Game Function ------------------------------------------------------------------//

// ----------------------------------------------------------- Load Game Function ------------------------------------------------------------------//
bool LoadGame() {
    // Open save file as a text file
    ifstream load_file("game_save.txt");

    if (!load_file) {
        cout << "No save file found!" << endl;
        return false;
    }

    int hp, sp, shield, base_a, crit_a, base_b, crit_b;

    // Read data from file in the same order it was saved
    if (!(load_file >> character_name)) return false;
    if (!(load_file >> character_age)) return false;
    if (!(load_file >> character_class_choice)) return false;
    if (!(load_file >> starting_floor)) return false;
    if (!(load_file >> hp)) return false;
    if (!(load_file >> sp)) return false;
    if (!(load_file >> shield)) return false;
    if (!(load_file >> base_a)) return false;
    if (!(load_file >> crit_a)) return false;
    if (!(load_file >> base_b)) return false;
    if (!(load_file >> crit_b)) return false;

    load_file.close();

    loadstate = 1;

    // Reinitialize player with saved stats
    Player.reset_status (hp, sp, base_a, crit_a, base_b, crit_b, (shield-5));

    cout << "Game loaded successfully!" << endl;
    cout << "Welcome back, " << character_name << "!" << endl;
    cout << "Current HP: " << Player.get_HP() << " \tSP: " << Player.get_SP() << endl <<endl;

    return true;
}
// ----------------------------------------------------------- Load Game Function ------------------------------------------------------------------//

// ----------------------------------------------------------- End Game Function ------------------------------------------------------------//
void Game_End ()
{
        char action;
        if (game_state)
        {
            cout << "Do you want to quit game ? [y/n]  ";
            cin  >> action;
                if(action == 'y' || action == 'Y')
                {
                    cout << "See you next time" << endl;
                    exit(0);
                }
                else
                {
                    cout << "Returning to the Game.." << endl <<endl;
                }
        }
        else
        {
            cout  << ".............You have been defeated........\n"
                    << "................Lost consciousness.................." << endl;
            exit (0);
        }
}
// ------------------------------------------------------- End of Close Game Function --------------------------------------------------------//

// ----------------------------------- Allocate the status for different class (similar to initialization) -----------------------------------//
void character_class_allocation()
{
        switch(character_class_choice)
        {
                case 1:
                {
                    cout << "Well met... " << character_name << endl
                            << "A Wander Paladin!" << endl
                            << "You have no choice but to move forward........." << endl << endl;
                    Player.set_HP(0,140);
                    Player.set_SP(0,3);
                    Player.set_base_a_crit_a(3, 6);
                    Player.set_base_b_crit_b(6, 15);
                    Player.set_Shield(5);
                }
                break;
                case 2:
                {
                    cout << "Well met...  " << character_name << endl
                            << "A Babarian Warrior!" << endl
                            << "You have no choice but to move forward........." << endl << endl;
                    Player.set_HP(0,120);
                    Player.set_SP(0,3);
                    Player.set_base_a_crit_a(4, 8);
                    Player.set_base_b_crit_b(8, 17);
                    Player.set_Shield(3);
                }
                break;
                case 3:
                {
                    cout << "Well met... " << character_name << endl
                            << "A Solo Ranger!" << endl
                            << "You have no choice but to move forward........." << endl << endl;
                    Player.set_HP(0,100);
                    Player.set_SP(0,4);
                    Player.set_base_a_crit_a(7, 10);
                    Player.set_base_b_crit_b(13, 18);
                    Player.set_Shield(2);
                }
                break;
                case 4:
                {
                    cout << "Well met... " << character_name << endl
                            << "A Wise Wizard!" << endl
                            << "You have no choice but to move forward........." << endl << endl;
                    Player.set_HP(0,100);
                    Player.set_SP(0,3);
                    Player.set_base_a_crit_a(1, 10);
                    Player.set_base_b_crit_b(12, 26);
                    Player.set_Shield(0);
                }
                break;
        }
}
// -------------------------------------------------------- End of allocation for player ----------------------------------------------------------//

// Declaring the Enemy Fighting Generator first //
void Enemy_Fighting_generator(int enemy_code);


//------------------------------------------------------ Start of Player Fighting Generator -------------------------------------------------------- //
void Fighting_generator(int enemy_code)
{
        int damage = 0;
        char action;
// ------------------------------------ Goblin ----------------------------------------//
    if(enemy_code == 1)
    {
            // Initializing the Goblin Status;
            Goblin.reset_status          (40, 3, 2, 4, 3, 5, 0);
            // player fight with goblin until one fall
            while(Player.get_HP() > 0 && Goblin.get_HP() > 0 )
            {
                // generating UI for the player to check statuss
                cout << "HP: " << Player.get_HP() << " SP: " << Player.get_SP() << endl;
                cout << "Goblin's HP: " << Goblin.get_HP() << endl << endl;
                cout << "Choose your action: ...." << endl;
                cout << "1. Normal Attack\t\t 2. Strong Attack" << endl;
                cout << "3. Defense\t\t\t 4. Quit Game" <<endl;
                cin  >> action;

                // switch case is used to monitor player action
                switch(action)
                {
                    case '1' :
                    {
                        // check if player have enough SP to attack
                        if(Player.get_SP() < 1)
                        {
                            cout << "You have not enough SP to use this action!!!" << endl;
                            break;
                        }
                        Player.set_SP(1,0);

                        damage = Player.set_Attack_a() - Goblin.get_Shield();
                        if (damage > 0){
                                cout << "You deal damage to Goblin! " << endl;
                                // calculating the damage deal to goblin
                                Goblin.set_HP(damage,0);
                        }
                        // recover the SP for player
                        Player.set_SP(0,1);
                        // it is the time for goblin to attack
                        if(Goblin.get_HP() > 0)       Enemy_Fighting_generator(1);
                    }
                    break;
                    case '2' :
                    {
                        if(Player.get_SP() < 2)
                        {
                            cout << "You have not enough SP to use this action!!!" << endl;
                            break;
                        }
                        Player.set_SP(2,0);

                        damage = Player.set_Attack_b() - Goblin.get_Shield();
                        if (damage > 0){
                            cout << "You deal a great damage to Goblin! " << endl;
                            Goblin.set_HP(damage,0);
                        }
                        Player.set_SP(0,1);
                        if(Goblin.get_HP() > 0)       Enemy_Fighting_generator(1);
                    }
                    break;
                    case '3' :
                    {
                        cout << "You try to defend an attack...." << endl;
                        // set the shield to be true
                        player_raise_shield = 1;
                        Player.set_SP(0,1);
                        if(Goblin.get_HP() > 0)       Enemy_Fighting_generator(1);
                    }
                    break;
                    case '4':
                        {
                            // Here player can quit the game
                            game_state = 1;
                            Game_End();
                        }
                    break;
                    default:
                        {
                            cout << "Please choose the suitable action.....! "<< endl;
                            break;
                        }
                }// end of switch case
                // deactivate the shield
                    player_raise_shield = 0;
                    enemy_raise_shield = 0;
            } // end of while loop
            // checking player HP
            if(Player.get_HP()>0)       cout << "You beat Goblin!!!" <<endl;
            else                                   { game_state = 0;   Game_End(); }      // Player lose
    }
// ------------------------------------ Goblin ----------------------------------------//

// ------------------------------------ Beast ----------------------------------------//
    if(enemy_code == 2)
    {
                // Initializing the Beast Status;
                Beast.reset_status            (50, 3, 3, 5, 4, 6, 0);
                // player fight with beast until one fall
                while(Player.get_HP() > 0 && Beast.get_HP() > 0 )
                {
                    // generating UI for the player to check statuss
                    cout << "HP: " << Player.get_HP() << " SP: " << Player.get_SP() << endl;
                    cout << "Beast's HP: " << Beast.get_HP() << endl << endl;
                    cout << "Choose your action: ...." << endl;
                    cout << "1. Normal Attack\t\t 2. Strong Attack" << endl;
                    cout << "3. Defense\t\t\t 4. Quit" <<endl;
                    cin  >> action;

                    // switch case is used to monitor player action
                    switch(action)
                    {
                        case '1' :
                        {
                            // check if player have enough SP to attack
                            if(Player.get_SP() < 1)
                            {
                                cout << "You have not enough SP to use this action!!!" << endl;
                                break;
                            }
                            Player.set_SP(1,0);

                            damage = Player.set_Attack_a() - Beast.get_Shield();
                            if (damage > 0){
                                    cout << "You deal damage to Beast! " << endl;
                                    // calculating the damage deal to Beast
                                    Beast.set_HP(damage,0);
                            }
                            // recover the SP for player
                            Player.set_SP(0,1);
                            if(Beast.get_HP() > 0)       Enemy_Fighting_generator(2);
                        }
                        break;
                        case '2' :
                        {
                            if(Player.get_SP() < 2)
                            {
                                cout << "You have not enough SP to use this action!!!" << endl;
                                break;
                            }
                            Player.set_SP(2,0);

                            damage = Player.set_Attack_b() - Beast.get_Shield();
                            if (damage > 0){
                                cout << "You deal a great damage to Beast! " << endl;
                                Beast.set_HP(damage,0);
                            }
                            Player.set_SP(0,1);
                            if(Beast.get_HP() > 0)       Enemy_Fighting_generator(2);
                        }
                        break;
                        case '3' :
                        {
                            cout << "You try to defend an attack...." << endl;
                            // set the shield to be true
                            player_raise_shield = 1;
                            Player.set_SP(0,1);
                            if(Beast.get_HP() > 0)       Enemy_Fighting_generator(2);
                        }
                        break;
                        case '4':
                            {
                                // Here player can quit the game
                                game_state = 1;
                                Game_End();
                            }
                        break;
                        default:
                        {
                            cout << "Please choose the suitable action.....! "<< endl;
                            break;
                        }
                    }// end of the switch case
                    // deactivate the shield
                    player_raise_shield = 0;
                    enemy_raise_shield = 0;
                } // end of while loop
                // checking player HP
                if(Player.get_HP()>0)       cout << "You beat Beast!!!" <<endl;
                else                                   { game_state = 0;   Game_End(); }      // Player lose
    }
// ------------------------------------ Beast ----------------------------------------//

// ------------------------------------ Explorer ----------------------------------------//
    if(enemy_code == 3)
    {
                // Explorer will know how to use defense, so we need to set condition for defense
                Explorer.reset_status               (50, 3, 3, 4, 4, 7, 1);
                while(Player.get_HP() > 0 && Explorer.get_HP() > 0 )
                {
                    // generating UI for the player to check statuss
                    cout << "HP: " << Player.get_HP() << " SP: " << Player.get_SP() << endl;
                    cout << "Explorer's HP: " << Explorer.get_HP() << endl << endl;
                    cout << "Choose your action: ...." << endl;
                    cout << "1. Normal Attack\t\t 2. Strong Attack" << endl;
                    cout << "3. Defense\t\t\t 4. Quit" <<endl;
                    cin  >> action;

                    switch(action)
                    {
                        case '1' :
                        {
                            if(Player.get_SP() < 1)
                            {
                                cout << "You have not enough SP to use this action!!!" << endl;
                                break;
                            }
                            Player.set_SP(1,0);

                            if (enemy_raise_shield)         damage = Player.set_Attack_a() - Explorer.get_Shield() - 5;  // 5 here stand for the explorer defense increase
                            else                                        damage = Player.set_Attack_a() - Explorer.get_Shield();
                            if (damage > 0){
                                    cout << "You deal damage to Explorer! " << endl;
                                    // calculating the damage deal to Explorer
                                    Explorer.set_HP(damage,0);
                            }
                            Player.set_SP(0,1);
                            if(Explorer.get_HP() > 0)       Enemy_Fighting_generator(3);
                        }
                        break;
                        case '2' :
                        {
                            if(Player.get_SP() < 2)
                            {
                                cout << "You have not enough SP to use this action!!!" << endl;
                                break;
                            }
                            Player.set_SP(2,0);

                            if (enemy_raise_shield)         damage = Player.set_Attack_a() - Explorer.get_Shield() - 5;  // 5 here stand for the explorer defense increase
                            else                                        damage = Player.set_Attack_a() - Explorer.get_Shield();
                            if (damage > 0){
                                cout << "You deal a great damage to Explorer! " << endl;
                                Explorer.set_HP(damage,0);
                            }
                            Player.set_SP(0,1);
                            if(Explorer.get_HP() > 0)       Enemy_Fighting_generator(3);
                        }
                        break;
                        case '3' :
                        {
                            cout << "You try to defend an attack...." << endl;
                            // set the shield to be true
                            player_raise_shield = 1;
                            Player.set_SP(0,1);
                            if(Explorer.get_HP() > 0)       Enemy_Fighting_generator(3);
                        }
                        break;
                        case '4':
                        {
                                // Here player can quit the game
                                game_state = 1;
                                Game_End();
                        }
                        break;
                        default:
                        {
                            cout << "Please choose the suitable action.....! "<< endl;
                            break;
                        }
                    }// end of the switch case
                    // deactivate the shield
                    player_raise_shield = 0;
                    enemy_raise_shield = 0;
                } // end of while loop
                // checking player HP
                if(Player.get_HP()>0)       cout << "You beat Explorer!!!" <<endl;
                else                                   { game_state = 0;   Game_End(); }      // Player lose
    }
// ------------------------------------ Explorer ----------------------------------------//

// ------------------------------------ Monster ----------------------------------------//
    if(enemy_code == 4)
    {
                // Monster is Rare encounter, it is dangerous since it have a high chance to use strong attack every turn
                // Initializing the Monster Status;
                Monster.reset_status        (60, 3, 3, 5, 4, 8, 1);
                // player fight with beast until one fall
                while(Player.get_HP() > 0 && Monster.get_HP() > 0 )
                {
                    // generating UI for the player to check statuss
                    cout << "HP: " << Player.get_HP() << " SP: " << Player.get_SP() << endl;
                    cout << "Monster's HP: " << Monster.get_HP() << endl << endl;
                    cout << "Choose your action: ...." << endl;
                    cout << "1. Normal Attack\t\t 2. Strong Attack" << endl;
                    cout << "3. Defense\t\t\t 4. Quit" <<endl;
                    cin  >> action;

                    // switch case is used to monitor player action
                    switch(action)
                    {
                        case '1' :
                        {
                            // check if player have enough SP to attack
                            if(Player.get_SP() < 1)
                            {
                                cout << "You have not enough SP to use this action!!!" << endl;
                                break;
                            }
                            Player.set_SP(1,0);

                            damage = Player.set_Attack_a() - Monster.get_Shield();
                            if (damage > 0){
                                    cout << "You deal damage to Monster! " << endl;
                                    // calculating the damage deal to Monster
                                    Monster.set_HP(damage,0);
                            }
                            // recover the SP for player
                            Player.set_SP(0,1);
                            if(Monster.get_HP() > 0)       Enemy_Fighting_generator(4);
                        }
                        break;
                        case '2' :
                        {
                            if(Player.get_SP() < 2)
                            {
                                cout << "You have not enough SP to use this action!!!" << endl;
                                break;
                            }
                            Player.set_SP(2,0);

                            damage = Player.set_Attack_b() - Monster.get_Shield();
                            if (damage > 0){
                                cout << "You deal a great damage to Monster! " << endl;
                                Monster.set_HP(damage,0);
                            }
                            Player.set_SP(0,1);
                            if(Monster.get_HP() > 0)       Enemy_Fighting_generator(4);
                        }
                        break;
                        case '3' :
                        {
                            cout << "You try to defend an attack...." << endl;
                            // set the shield to be true
                            player_raise_shield = 1;
                            Player.set_SP(0,1);
                            if(Monster.get_HP() > 0)       Enemy_Fighting_generator(4);
                        }
                        break;
                        case '4':
                            {
                                // Here player can quit the game
                                game_state = 1;
                                Game_End();
                            }
                        break;
                        default:
                        {
                            cout << "Please choose the suitable action.....! "<< endl;
                            break;
                        }
                    }// end of the switch case
                    // deactivate the shield
                    player_raise_shield = 0;
                    enemy_raise_shield = 0;
                } // end of while loop
                // checking player HP
                if(Player.get_HP()>0)       cout << "You beat Monster!!!" <<endl;
                else                                   { game_state = 0;   Game_End(); }      // Player lose
    }
// ------------------------------------ Monster ----------------------------------------//

// ------------------------------------ Demon Nemesis ----------------------------------------//
    if (enemy_code == 5)
    {
            // Demon Nemesis is the final boss of the dungeon, A new born Demon from nourish of Dungeon.
            // It has high HP, and often use strong attack against player, although it do not defend but has high defense
            Demon_Nemesis.reset_status    (110, 3, 5, 6, 6, 8, 4);

             while(Player.get_HP() > 0 && Demon_Nemesis.get_HP() > 0 )
                {
                    // generating UI for the player to check statuss
                    cout << "HP: " << Player.get_HP() << " SP: " << Player.get_SP() << endl;
                    cout << "Demon Nemesis's HP: " << Demon_Nemesis.get_HP() << endl << endl;
                    cout << "Choose your action: ...." << endl;
                    cout << "1. Normal Attack\t\t 2. Strong Attack" << endl;
                    cout << "3. Defense\t\t\t 4. Quit" <<endl;
                    cin  >> action;

            switch(action)
                    {
                        case '1' :
                        {
                            // check if player have enough SP to attack
                            if(Player.get_SP() < 1)
                            {
                                cout << "You have not enough SP to use this action!!!" << endl;
                                break;
                            }
                            Player.set_SP(1,0);

                            damage = Player.set_Attack_a() - Demon_Nemesis.get_Shield();
                            if (damage > 0){
                                    cout << "You deal damage to Demon Nemesis! " << endl;
                                    // calculating the damage deal to Demon_Nemesis
                                    Demon_Nemesis.set_HP(damage,0);
                            }
                            // recover the SP for player
                            Player.set_SP(0,1);
                            if(Demon_Nemesis.get_HP() > 0)       Enemy_Fighting_generator(5);
                        }
                        break;
                        case '2' :
                        {
                            if(Player.get_SP() < 2)
                            {
                                cout << "You have not enough SP to use this action!!!" << endl;
                                break;
                            }
                            Player.set_SP(2,0);

                            damage = Player.set_Attack_b() - Demon_Nemesis.get_Shield();
                            if (damage > 0){
                                cout << "You deal a great damage to Demon Nemesis! " << endl;
                                Demon_Nemesis.set_HP(damage,0);
                            }
                            Player.set_SP(0,1);
                            if(Demon_Nemesis.get_HP() > 0)       Enemy_Fighting_generator(5);
                        }
                        break;
                        case '3' :
                        {
                            cout << "You try to defend an attack...." << endl;
                            // set the shield to be true
                            player_raise_shield = 1;
                            Player.set_SP(0,1);
                            if(Demon_Nemesis.get_HP() > 0)       Enemy_Fighting_generator(5);
                        }
                        break;
                        case '4':
                            {
                                // Here player can quit the game
                                game_state = 1;
                                Game_End();
                            }
                        break;
                        default:
                        {
                            cout << "Please choose the suitable action.....! "<< endl;
                            break;
                        }
                    }// end of the switch case
                    // deactivate the shield
                    player_raise_shield = 0;
                    enemy_raise_shield = 0;
                } // end of while loop
                // checking player HP
                if(Player.get_HP()>0)
                {

                    cout << "You beat Demon Nemesis!!! \n" << endl;
                    cout << "Press any key to continue........";
                    system("cls");
                    cout << "The Dungeon Boss has been eliminated !!! \n"
                            << endl
                            << "Congratulation ! You conquer the Dungeon Nemesis !!!!" << endl;
                    game_complete = 1;
                }
                else                                   { game_state = 0;   Game_End(); }      // Player lose
    }
// ------------------------------------ Demon Nemesis ----------------------------------------//

}
//------------------------------------------------------ End of Player Fighting Generator -------------------------------------------------------- //

//------------------------------------------------------ Start of Enemy Fighting Generator ------------------------------------------------------ //
void Enemy_Fighting_generator(int enemy_code)
{
        int damage =0;
        int enemy_attk;
// ------------------------------------ Goblin ----------------------------------------//
        if(enemy_code == 1)
        {
            //This is the Goblin movement generator.....
            // Goblin will have only two movement, attack or observation (not using sp)
            enemy_attk = rand() % 10;
                    if (enemy_attk < 3 )
                    {
                        cout << "Goblin is finding chance to attack....." << endl;
                    }
                    else if ( enemy_attk < 7 )
                    {
                        if (player_raise_shield)       damage = Goblin.set_Attack_a() - Player.get_Shield();
                        else                                      damage = Goblin.set_Attack_a();
                        if (damage > 0){
                            // Player damage calculator
                                Player.set_HP(damage,0);
                                cout << "Goblin deal damage to you !" << endl;
                        }
                        else    cout << "Successful defense !" << endl;

                    }
                    else
                    {
                       if (player_raise_shield)       damage = Goblin.set_Attack_b() - Player.get_Shield();
                       else                                      damage = Goblin.set_Attack_b();
                       if (damage > 0){
                            // Player damage calculator
                                Player.set_HP(damage,0);
                                cout << "!! Goblin deal a great damage to you !!!" << endl;
                       }
                       else    cout << "Successful defense !" << endl;

                    }
                cout << endl;   // formating the output
        }
// ------------------------------------ Goblin ----------------------------------------//

// ------------------------------------ Beast ----------------------------------------//
        if (enemy_code == 2)
        {
            // This is the Beast movement generator.....
            // Beast only do attack, and continuously, player need to finish them quickly
             enemy_attk = rand() % 10;
            if (enemy_attk < 7)
            {
                        if (player_raise_shield)       damage = Beast.set_Attack_a() - Player.get_Shield();
                        else                                      damage = Beast.set_Attack_a();
                        if (damage > 0){
                            // Player damage calculator
                                Player.set_HP(damage,0);
                                cout << "Beast deal damage to you !" << endl;
                        }
                        else    cout << "Successful defense !" << endl;

            }
            else
            {
                        if (player_raise_shield)       damage = Beast.set_Attack_b() - Player.get_Shield();
                       else                                       damage = Beast.set_Attack_b();
                       if (damage > 0){
                            // Player damage calculator
                                Player.set_HP(damage,0);
                                cout << "!! Beast deal a great damage to you !!!" << endl;
                       }
                       else    cout << "Successful defense !" << endl;
            }
            cout << endl;   // formating the output
        }
// ------------------------------------ Beast ----------------------------------------//

// ------------------------------------ Explorer ----------------------------------------//
        if (enemy_code ==3)
        {
            // This is the Explorer movement generator......
            // Explorer will use defense, so it is more tricky to deal with them
             enemy_attk = rand() % 10;
            if (enemy_attk  < 5 )
            {
                        if (player_raise_shield)       damage = Explorer.set_Attack_a() - Player.get_Shield();
                        else                                      damage = Explorer.set_Attack_a();
                        if (damage > 0){
                            // Player damage calculator
                                Player.set_HP(damage,0);
                                cout << "Explorer deal damage to you !" << endl;
                        }
                        else    cout << "Successful defense !" << endl;
            }
            else if (enemy_attk < 7)
            {
                       if (player_raise_shield)       damage = Explorer.set_Attack_b() - Player.get_Shield();
                       else                                       damage = Explorer.set_Attack_b();
                       if (damage > 0){
                            // Player damage calculator
                                Player.set_HP(damage,0);
                                cout << "!! Explorer deal a great damage to you !!!" << endl;
                       }
                       else    cout << "Successful defense !" << endl;
            }
            else
            {
                enemy_raise_shield = 1;
                cout << "Explorer is defenting" << endl;
            }
            cout << endl;
        }
// ------------------------------------ Explorer ----------------------------------------//

// ------------------------------------ Monster ----------------------------------------//
        if (enemy_code ==4)
        {
            // This is the Monster movement generator......
             enemy_attk = rand() % 10;
            if (enemy_attk  < 4 )
            {
                        if (player_raise_shield)       damage = Monster.set_Attack_a() - Player.get_Shield();
                        else                                      damage = Monster.set_Attack_a();
                        if (damage > 0){
                            // Player damage calculator
                                Player.set_HP(damage,0);
                                cout << "Monster deal damage to you !" << endl;
                        }
                        else    cout << "Successful defense !" << endl;
            }
            else
            {
                       if (player_raise_shield)       damage = Monster.set_Attack_b() - Player.get_Shield();
                       else                                       damage = Monster.set_Attack_b();
                       if (damage > 0){
                            // Player damage calculator
                                Player.set_HP(damage,0);
                                cout << "!! Monster deal a great damage to you !!!" << endl;
                       }
                       else    cout << "Successful defense !" << endl;
            }
            cout << endl;
        }
// ------------------------------------ Monster ----------------------------------------//

// ------------------------------------ Demon Nemesis ----------------------------------------//
        if (enemy_code ==5)
        {
            // This is the Demon_Nemesis movement generator......
            // Demon Nemesis will use SP attack when it's SP reach 3
             enemy_attk = rand() % 10;
            if(Demon_Nemesis.get_SP() > 2)
            {
                        Demon_Nemesis.set_SP(3,0);
                        damage = 10; //fixed damage from SP attack by Demon Nemesis
                        Player.set_HP(damage,0);
                        cout << "Demon Nemesis Use strong SP attack !!!\n"
                                <<  "Dealing Fixed Damage to you !!" <<endl;

            }
            else
            {
                            if (enemy_attk  < 4 )
                            {
                                    if (player_raise_shield)       damage = Demon_Nemesis.set_Attack_a() - Player.get_Shield();
                                    else                                      damage = Demon_Nemesis.set_Attack_a();
                                    if (damage > 0){
                                        // Player damage calculator
                                            Player.set_HP(damage,0);
                                            cout << "Demon Nemesis deal damage to you !" << endl;
                                    }
                                    else    cout << "Successful defense !" << endl;
                                    Demon_Nemesis.set_SP(0,1);
                            }
                            else
                            {
                                    if (player_raise_shield)       damage = Demon_Nemesis.set_Attack_b() - Player.get_Shield();
                                    else                                       damage = Demon_Nemesis.set_Attack_b();
                                    if (damage > 0){
                                        // Player damage calculator
                                            Player.set_HP(damage,0);
                                            cout << "!! Demon Nemesis deal a great damage to you !!!" << endl;
                                    }
                                    else    cout << "Successful defense !" << endl;
                                    Demon_Nemesis.set_SP(0,1);
                            }

            }
            cout << endl;
        }
// ------------------------------------ Demon Nemesis ----------------------------------------//

}

//------------------------------------------------------ End of Enemy Fighting Generator -------------------------------------------------- //

//------------------------------------------------------ Level Generator ----------------------------------------------------------------- //
void Level_generator_low(bool loadstate)
{
            int event;
            if (!loadstate)
                starting_floor =1;

        /*    // Check for save file at start (before the looping of the game)
            if (LoadGame()){
                    // Implementation continues with saved progress
                    // adjust the starting floor based on save data
                    starting_floor = save.current_floor;
            }*/

            for (int level = starting_floor ; level < 7 ; level++)
            {
                // showing current floor of the dungeon
                cout << "----------You are now in floor " << level << " -------------"<< endl;
                // using rand to generate random event
                event = rand() % 10;

                // Add save option at the start of each floor
                cout << "Would you like to save your progress? (y/n): ";
                char save_choice;
                cin >> save_choice;
                if (save_choice == 'y' || save_choice == 'Y') {
                        SaveGame(level);
                }
                else        cout << "Skip Save..." <<endl << endl;

                // First, the Boss will occur at level 6 ( if we start from level 1)
                if (level == 6)
                {
                    cout << "!!!    You encounter a Demon     !!!\n"
                            << "    It could be the Nemesis !      " << endl;
                            Fighting_generator(5);
                }


                // Then, at level 5, player might encounter 2 type of event, one is normal camping recover
                // another is player find a recover springs, that recover more health
                if (level == 5)
                {
                    if (event < 5)
                    {
                        cout << "You find yourself a place to rest......" <<endl
                                << "Camping now........" <<endl
                                << "HP recover 20..........." << endl << endl;
                        Player.set_HP(0,20);
                    }
                    else
                    {
                        cout << "You find a healing spring !!!!" << endl
                                << "Camping now........" <<endl
                                << "HP recover 30..........." << endl << endl;
                        Player.set_HP(0,30);

                    }
                }

                else // the rest is the normal event before level 5
                {
                        if ( event < 3 )
                        {
                        cout << "You encounter Goblin.....!" << endl;
                        Fighting_generator(1);
                        }
                        else if( event > 2 && event < 6)
                        {
                        cout << "You encounter Beast.....!" << endl;
                        Fighting_generator(2);
                        }
                        else if ( event >5 && event <9)
                        {
                        cout << "You encounter Explorer....!" << endl;
                        Fighting_generator(3);
                        }
                        else
                        {
                         cout << "You encounter Monster....!" << endl;
                        Fighting_generator(4);
                        }

                }
            }
}
//------------------------------------------------------ End of Level Generator -------------------------------------------------------- //


// --------------------------------------------------------------------- Here is the main function --------------------------------------------------------------//
int main()
{

        Welcome_to_the_Game();

        // set the game start (boolean true)
        game_state = 1;

        /** Start the Game */
        getch();
        system("cls");

        srand(seed);

        // Add load game option
        cout << "1. New Game\n2. Load Game\nEnter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 2) {
            if (!LoadGame()) {
                choice = 1;
            }
        }
        if (choice == 1) {

                    cout << "Starting new game..." << endl;
                    getch();
                    system("cls");

                    // Introduction of the Dungeon....
                    Introduction();
                    // Small Break
                    cout << "Press any key to continue......";
                    getch();
                    system("cls");


                    // Building player
                    character_building();
                    character_class_allocation();

                    // Small Break
                    cout << "Press any key to continue......";
                    getch();
                    system("cls");

        }

        // -------- START GAME -----------//
        // Generating the level and start playing the game
        Level_generator_low(loadstate);


        if (game_complete)

            cout << "You Finish the Game!" << endl;




    return 0;
}
// --------------------------------------------------------------------------------- END --------------------------------------------------------------------------------------//
