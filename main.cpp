#include <iostream>
#include <vector>
#include <iomanip> // 用于格式化输出

// ---------------------------------------------------------
// 1. 定义数据结构 (就像 MB-System 定义 mb_structure 一样)
// ---------------------------------------------------------

// 定义单波束的数据结构
struct Beam {
    int id;             // 波束编号 (例如：第1号波束)
    double angle;       // 波束角度 (度)
    double depth;       // 测量的水深 (米)
    double intensity;   // 回波强度 (dB) - 这就是你感兴趣的强度数据！
};

// 定义一个 Ping (一次声纳发射) 的结构
struct SonarPing {
    long long timestamp;     // 时间戳
    double ship_heading;     // 船的航向 (0-360度)
    std::vector<Beam> beams; // 包含多个波束的动态数组
};

// ---------------------------------------------------------
// 2. 主函数 (程序的入口)
// ---------------------------------------------------------

int main() {
    // 创建一个 Ping 对象变量
    SonarPing currentPing;

    // 模拟设置这个 Ping 的基本信息
    currentPing.timestamp = 1716345600; // 模拟一个时间戳
    currentPing.ship_heading = 90.5;    // 船正向东航行

    // 模拟接收到了 3 个波束的数据
    // 这里的 push_back 意思是往数组里“塞”数据
    currentPing.beams.push_back({1, -45.0, 100.5, -20.0}); // 左侧波束
    currentPing.beams.push_back({2,   0.0,  98.2, -15.5}); // 中央波束
    currentPing.beams.push_back({3,  45.0, 100.8, -21.0}); // 右侧波束
    currentPing.beams.push_back({4, 60.0, 105.0, -22.5}); //新增第四个数据

    // -----------------------------------------------------
    // 3. 数据处理与输出 (模拟 MB-System 的数据查看功能)
    // -----------------------------------------------------

    std::cout << "=== 声纳 Ping 数据概览 ===" << std::endl;
    std::cout << "时间戳: " << currentPing.timestamp << std::endl;
    std::cout << "船航向: " << currentPing.ship_heading << " 度" << std::endl;
    std::cout << "----------------------------" << std::endl;

    // 使用循环遍历所有波束，打印它们的详细信息
    // 这里的 auto& beam 表示：自动获取 beams 里的每一个元素
    for (const auto& beam : currentPing.beams) {
        if (beam.depth > 100){
        std::cout << "波束 ID: " << beam.id 
                  << " | 角度: " << std::setw(6) << beam.angle 
                  << " | 深度: " << beam.depth << "m"
                  << " | 强度: " << beam.intensity << "dB" 
                  << std::endl;
        }
    }

    return 0; // 程序成功结束
}