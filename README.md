# Snippets

代码片段仓库 - C++ 算法与模板元编程技巧集合

---

## 📦 仓库总览

本仓库收集了各类 C++ 代码片段，涵盖经典算法实现、模板元编程技巧、多线程工具等。使用 CMake 构建，支持 C++17/20 标准，集成 Catch2 测试框架和 nanobench 性能测试。

---

## 📁 目录结构

### 1. `sort/` - 排序算法
经典排序算法的实现：
- **bubble_sort/** - 冒泡排序
- **merge_sort/** - 归并排序
- **selection_sort/** - 选择排序
- **strange_sort/** - 趣味排序
  - `monkey_sort` - 猴子排序（随机排序）
  - `sleep_sort` - 睡眠排序

### 2. `find_way/` - 寻路算法
路径搜索算法的实现：
- **astar/** - A* 寻路算法
- **bfs/** - 广度优先搜索
- **dfs/** - 深度优先搜索
- `base.h` - 公共基础定义

### 3. `mthread/` - 多线程工具
多线程相关工具类：
- **thread_guard/** - 线程守卫（RAII 管理线程）
- **thread_task/** - 线程任务封装
- **msg_queue/** - 消息队列
- **mutex_with_count/** - 带计数功能的互斥锁

### 4. `others/` - 其他工具
实用工具集合：
- **para_binding/** - 参数绑定
- **timer/** - 计时器
- **x_macro_patterns/** - X-Macro 模式演示
- **det_mutex_conflict/** - 互斥锁冲突检测（含 shared_mutex 版本）

### 5. `tempo/` - 模板元编程
展示各种 C++ 模板技巧：
- **crtp/** - CRTP 经典实现
- **static_crtp/** - 静态 CRTP
- **static_reflection/** - C++17 静态反射实现
- **tuple_for_each/** - 利用折叠表达式遍历 tuple
- **calc_array_size/** - 编译期计算数组长度
- **empty_class_checker/** - 检查是否为空类
- **general_factory/** - 通用工厂模式 + 离线注册
- **member_wrapper/** - 成员包装器（检查类是否有某成员）
- **my_smart_ptr/** - 自实现智能指针（侵入式 & 非侵入式）
- **dt/** - 数据表 (Data Table) 的多种实现
- **bitset/** - 位图实现（静态/动态）
- **scope_guard/** - 作用域守卫
- **class_unity/** - 类统一处理
- **map_macro_to_struct/** - 宏映射到结构体
- **data_container/** - 数据容器

---

## 🛠️ 构建与使用

### 依赖
- CMake 3.17+
- C++17 (tempo 模块) / C++20 (主项目)
- Catch2 v3（自动通过 FetchContent 获取）
- nanobench（自动通过 FetchContent 获取）

### 构建
```bash
mkdir build && cd build
cmake ..
make
```

### 运行测试
```bash
./Snippets    # 主项目测试
./Tempo       # tempo 模块测试
```

---

## 🎯 适用场景

- 学习 C++ 模板元编程技巧
- 参考经典算法实现
- 多线程编程工具复用
- 设计模式（工厂、CRTP 等）实践参考

---

## 📄 License

MIT License
