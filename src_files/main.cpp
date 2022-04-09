
/****************************************************************************************************
 *                                                                                                  *
 *                                     Koivisto UCI Chess engine                                    *
 *                                   by. Kim Kahre and Finn Eggers                                  *
 *                                                                                                  *
 *                 Koivisto is free software: you can redistribute it and/or modify                 *
 *               it under the terms of the GNU General Public License as published by               *
 *                 the Free Software Foundation, either version 3 of the License, or                *
 *                                (at your option) any later version.                               *
 *                    Koivisto is distributed in the hope that it will be useful,                   *
 *                  but WITHOUT ANY WARRANTY; without even the implied warranty of                  *
 *                   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                  *
 *                           GNU General Public License for more details.                           *
 *                 You should have received a copy of the GNU General Public License                *
 *                 along with Koivisto.  If not, see <http://www.gnu.org/licenses/>.                *
 *                                                                                                  *
 ****************************************************************************************************/

#include "uci.h"
#ifdef GENERATOR
#include "generator/genpool.h"
#endif

std::string getV(const std::vector<std::string>& vec, const std::string& key) {
    int index = 0;
    for (const std::string& s : vec) {
        if (s == key) {
            return vec.at(index + 1);
        }
        index++;
    }
    return "";
}

int main(int argc, char *argv[]) {


    #ifdef GENERATOR
        bb::init();
        nn::init();
        Game::init(argc, argv);
        
        std::vector<std::string> args(argv, argv + argc);
    
        auto getParam =
            [&](std::string const& option, int def)
        {
            std::string val = getV(args, option);
            return val.size() ? std::stoi(val) : def;
        };
    
        GeneratorPool pool(getParam("-threads", 1));
        pool.run(getParam("-games", 10));
    #else
    uci::mainloop(argc, argv);
    #endif
    return 0;
}
