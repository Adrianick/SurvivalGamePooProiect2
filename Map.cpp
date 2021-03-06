#include "Map.h"
//
// Created by Adrian on 3/30/2018.
//
#include <random>
#include <chrono>
#include "Agent_Type1.h"
#include "Agent_Type2.h"
#include "Agent_Type3.h"
#include "Item_Type1.h"
#include "Item_Type2.h"
#include "Item_Type3.h"

Map::Map() {

    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);

    numberOfAgentsAlive = 20;
    numberOfItemsAvailable = 15;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            mapOfTheGame[i][j] = 0;
        }
    } /// Harta este goala, doar 0

    for (int i = 1; i <= 9; i++) /// Creare agent_type1 in numar de 9
    {
        agents.insert(std::make_pair(i, new Agent_Type1()));
        agents.find(i)->second->setId(i);
        int linie, coloana;
        while (true) {
            linie = e() % 15, coloana = e() % 15;
            if (mapOfTheGame[linie][coloana] == 0) {
                agents.find(i)->second->setPosition(linie, coloana);
                mapOfTheGame[linie][coloana] = i;
                break;
            }
        }
    }
    for (int i = 10; i <= 15; i++) /// Creare agent_type2 in numar de 6
    {
        agents.insert(std::make_pair(i, new Agent_Type2()));
        agents.find(i)->second->setId(i);
        int linie, coloana;
        while (true) {
            linie = e() % 15, coloana = e() % 15;
            if (mapOfTheGame[linie][coloana] == 0) {
                agents.find(i)->second->setPosition(linie, coloana);
                mapOfTheGame[linie][coloana] = i;
                break;
            }
        }
    }

    for (int i = 16; i <= 20; i++) /// Creare agent_type3 in numar de 5
    {
        agents.insert(std::make_pair(i, new Agent_Type3()));
        agents.find(i)->second->setId(i);
        int linie, coloana;
        while (true) {
            linie = e() % 15, coloana = e() % 15;
            if (mapOfTheGame[linie][coloana] == 0) {
                agents.find(i)->second->setPosition(linie, coloana);
                mapOfTheGame[linie][coloana] = i;
                break;
            }
        }
    }


    for (int i = -1; i >= -5; i--) /// Creare item_type1 in numar de 5
    {
        items.insert(std::make_pair(i, new Item_Type1()));
        items.find(i)->second->setItemId(i);
        int linie, coloana;
        while (true) {
            linie = e() % 15, coloana = e() % 15;
            if (mapOfTheGame[linie][coloana] == 0) {
                items.find(i)->second->setItemPosition(linie, coloana);
                mapOfTheGame[linie][coloana] = i;
                break;
            }
        }
    }
    for (int i = -6; i >= -10; i--) /// Creare item_type1 in numar de 5
    {
        items.insert(std::make_pair(i, new Item_Type2()));
        items.find(i)->second->setItemId(i);
        int linie, coloana;
        while (true) {
            linie = e() % 15, coloana = e() % 15;
            if (mapOfTheGame[linie][coloana] == 0) {
                items.find(i)->second->setItemPosition(linie, coloana);
                mapOfTheGame[linie][coloana] = i;
                break;
            }
        }
    }
    for (int i = -11; i >= -15; i--) /// Creare item_type1 in numar de 5
    {
        items.insert(std::make_pair(i, new Item_Type3()));
        items.find(i)->second->setItemId(i);
        int linie, coloana;
        while (true) {
            linie = e() % 15, coloana = e() % 15;
            if (mapOfTheGame[linie][coloana] == 0) {
                items.find(i)->second->setItemPosition(linie, coloana);
                mapOfTheGame[linie][coloana] = i;
                break;
            }
        }
    }


    std::cout << "Harta initiala  arata astfel: \n";
    std::cout << *this; // afisare harta
}

void Map::setNumberOfItemsAvailable(int items) {
    numberOfItemsAvailable = items;
}

void Map::getNrAg() {
    std::cout << numberOfAgentsAlive;
}

void Map::simulareJoc() {
    int nrRunde = 0;
    while (numberOfAgentsAlive > 1) {
        rundaJoc();
        nrRunde++;

        if (nrRunde % 5 == 0) {
            for (auto i : items)
                i.second->decayItem();
        }
    }
    std::cout << "Agentul castigator este : " << agents.begin()->first << " ";

    if (agents.begin()->second->getItemEquiped() != 0)
        std::cout << " si a castigat manuind item-ul : " << agents.begin()->second->getItemEquiped()
                  << " viata : " << agents.begin()->second->getHealth() << " si damage : "
                  << agents.begin()->second->getDamage();

    std::cout << "\n";
    std::cout << "Numar total de runde : " << nrRunde << "\n";
    std::cout << "SIMULARE TERMINATA! \n";
}

void Map::simulareRunde() {
    int nrRunde = 0;
    char c;
    while (numberOfAgentsAlive > 1) {
        std::cout << "Vrei sa continui la urmatoarea runda? Apasa orice litera inafara de 'n' :";
        std::cin >> c;
        if (c == 'n')
            break;
        rundaJoc();
        nrRunde++;

        if (nrRunde % 5 == 0) {
            for (auto i : items)
                i.second->decayItem();
        }
    }

    if (numberOfAgentsAlive == 1) {
        std::cout << "Agentul castigator este : " << agents.begin()->first << " ";
        if (agents.begin()->second->getItemEquiped() != 0)
            std::cout << " si a castigat manuind item-ul : " << agents.begin()->second->getItemEquiped();
    } else
        std::cout << " Nici un castigator deoarece sunt mai multi agenti in viata  \n";


    std::cout << "\n";
    std::cout << "Numar total de runde : " << nrRunde << "\n";
    std::cout << "SIMULARE TERMINATA! \n";
}

void Map::rundaJoc() {
    for (auto it = agents.begin(); it != agents.end(); ++it) {

        if ((*it).second->getHealth() < 1)
            continue;

        int desters = (*it).second->moveAgent(mapOfTheGame, agents, items);
        if (desters > 0) {
            numberOfAgentsAlive--;
        }

        numberOfItemsAvailable = items.size();
    }
    for (int i = 1; i <= 20; ++i) {
        if (agents.count(i))
            if (agents.find(i)->second->getHealth() < 1) {
                delete agents.find(i)->second;
                agents.erase(i);
            }
    }
    afisareInformatiiCurente();
}

std::ostream &operator<<(std::ostream &o, Map &harta) {
    o << " X  |Y: ";
    for (int i = 1; i <= 15; i++) {
        o << i << "  ";
        if (i < 10)
            o << " ";
    }
    o << "\n";
    for (int i = 1; i <= 70; i++) {
        o << "_";
    }
    o << "\n";

    for (int i = 0; i < 15; i++) {
        if (i < 9) o << " ";
        o << i + 1 << "  |   ";
        for (int j = 0; j < 15; j++) {
            o << harta.mapOfTheGame[i][j] << " ";
            if (harta.mapOfTheGame[i][j] > -10)
                o << " ";
            if (harta.mapOfTheGame[i][j] <= 9 && harta.mapOfTheGame[i][j] >= 0) o << " ";
        }
        o << "| \n\n";
    }
    for (int i = 1; i <= 70; i++) {
        o << "-";
    }
    o << "\n";

    return o;
}

void Map::afisareInformatiiCurente() {
    std::cout << *this;
    std::cout << "Agenti in viata : " << numberOfAgentsAlive << "\n";
    std::cout << "Iteme pe harta : " << numberOfItemsAvailable << "\n\n";
}