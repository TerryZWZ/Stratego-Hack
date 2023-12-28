#include "game.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <cstdlib>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {
    string option;
    bool graphics = false;
    string cmd;

    bool chooseAbilityP1 = false;
    bool chooseAbilityP2 = false;
    bool setLinkP1 = false;
    bool setLinkP2 = false;

    string abilitiesP1;
    string abilitiesP2;
    string linkFileP1;
    string linkFileP2;

    for (int i = 1; i < argc; ++i) {
        option = argv[i];

        if (option == "-graphics") {
            graphics = true;
        }
        else if (option == "-ability1") {
            i++;
            abilitiesP1 = argv[i];
            chooseAbilityP1 = true;
        }
        else if (option == "-ability2") {
            i++;
            abilitiesP2 = argv[i];
            chooseAbilityP2 = true;
        }
        else if (option == "-link1"){
            linkFileP1 = argv[++i];
            setLinkP1 = true;
        }
        else if (option == "-link2"){
            linkFileP2 = argv[++i];
            setLinkP2 = true;
        }
    } 
    unique_ptr<Game> g = make_unique<Game>(graphics);

    if (chooseAbilityP1) {
        g->addAbility("p1", abilitiesP1);
    }
    if (chooseAbilityP2) {
        g->addAbility("p2", abilitiesP2);
    }
    if (setLinkP1) {
        ifstream filename{linkFileP1};
        g->addLinks(1, filename);
    }
    if (setLinkP2) {
        ifstream filename{linkFileP2};
        g->addLinks(2, filename);
    }

    // if abilities aren't specified, use default (LFDSP)
    if (!chooseAbilityP1) {
        g->addAbility("p1", "LFDSP");
    }
    if (!chooseAbilityP2) {
        g->addAbility("p2", "LFDSP");
    }
    // if links aren't specified, randomize order
    srand(time(0));
    if (!setLinkP1) {
        stringstream linksInput;
        vector<string> links = {"D1", "D2", "D3", "D4", "V1", "V2", "V3", "V4"};
        for (int i = 0; i < 8; ++i) { // 8 links
            int index = rand() % (links.size()); // gets random index from 0 to links.size()
            string link = links[index]; // get the link at index
            linksInput << link << "\n"; // write to stringstream
            links.erase(links.begin() + index); // remove link at index b/c unique links
        }
        g->addLinks(1, linksInput);
    }
    if (!setLinkP2) {
        stringstream linksInput;
        vector<string> links = {"D1", "D2", "D3", "D4", "V1", "V2", "V3", "V4"};
        for (int i = 0; i < 8; ++i) { // 8 links
            int index = rand() % (links.size()); // gets random index from 0 to links.size()
            string link = links[index]; // get the link at index
            linksInput << link << "\n"; // write to stringstream
            links.erase(links.begin() + index); // remove link at index b/c unique links
        }
        g->addLinks(2, linksInput);
    }
    g->runGame();
}
