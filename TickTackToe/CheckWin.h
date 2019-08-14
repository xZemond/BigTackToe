#include "Field.h"
#include "StaticData.h"

namespace checkWin {
   extern std::shared_ptr<Field> n_field;
   extern int n_fieldSize;
   extern Color n_color;
   extern std::tuple<int, int> n_position;
   extern int n_winSize;
   bool all(Color color, std::tuple<int, int> position, std::shared_ptr<Field> field);
   bool vertical();
   bool horizontal();
   bool rising();
   bool falling();
}
