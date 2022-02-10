#include <iostream>

/**
    1. 解析命令行参数，使用成熟的开源框架：
        优点：细节和易错点都帮你作好了，稳定性高；
              有使用经验和demo可以参考，易维护；
              照例子使用，提高开发速度。
*/
int main(int argc, char** argv)
{
    google::ParseCommandLineFlags(&argc, &argv, true);
}

