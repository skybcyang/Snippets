# Snippets

代码片段仓库 - C++ 算法、并发、设计模式与模板元编程技巧集合

---

## 📦 仓库总览

本仓库收集了各类 C++ 代码片段，按技术领域和用途重新组织，涵盖：
- **Algorithm** - 经典算法实现
- **Concurrency** - 并发编程工具
- **Container** - 数据结构
- **Pattern** - 设计模式
- **Metaprogramming** - 模板元编程
- **Utility** - 实用工具

使用 CMake 构建，支持 C++17/20 标准，集成 Catch2 测试框架和 nanobench 性能测试。

---

## 📁 目录结构

### `algorithm/` - 算法

#### `algorithm/sort/` - 排序算法
- **bubble_sort/** - 冒泡排序
- **merge_sort/** - 归并排序
- **selection_sort/** - 选择排序
- **strange_sort/** - 趣味排序
  - `monkey_sort` - 猴子排序（随机排序）
  - `sleep_sort` - 睡眠排序

#### `algorithm/graph/` - 图算法
- **astar/** - A* 寻路算法
- **bfs/** - 广度优先搜索
- **dfs/** - 深度优先搜索

---

### `concurrency/` - 并发编程

#### `concurrency/thread/` - 线程管理
- **thread_guard/** - 线程守卫（RAII 管理线程）
- **thread_task/** - 线程任务封装

#### `concurrency/sync/` - 同步原语
- **mutex_with_count/** - 带计数功能的互斥锁
- **det_mutex_conflict/** - 互斥锁冲突检测

#### `concurrency/queue/` - 并发队列
- **msg_queue/** - 消息队列
- **lockfree_queue/** - 无锁队列
  - 基于 Michael-Scott 算法的无界队列
  - 固定大小的有界队列

#### `concurrency/pool/` - 线程池
- **thread_pool/** - 固定大小线程池

---

### `container/` - 数据结构

#### `container/cache/` - 缓存
- **lru_cache/** - LRU (Least Recently Used) 缓存

#### `container/smart_ptr/` - 智能指针
- **intrusive/** - 侵入式智能指针
- **non_intrusive/** - 非侵入式智能指针

---

### `pattern/` - 设计模式

#### `pattern/creational/` - 创建型模式
- **singleton/** - 单例模式
  - Meyer's Singleton
  - 模板基类单例
  - 双检查锁单例

#### `pattern/behavioral/` - 行为型模式
- **observer/** - 观察者模式
  - 单线程/多线程安全版本
  - RAII 订阅守卫

#### `pattern/structural/` - 结构型模式
- **crtp/** - CRTP (Curiously Recurring Template Pattern)

---

### `metaprogramming/` - 模板元编程

#### `metaprogramming/type_traits/` - 类型萃取
- **empty_class_checker/** - 检查是否为空类
- **member_wrapper/** - 成员包装器

#### `metaprogramming/static_reflection/` - 静态反射

#### `metaprogramming/tuple/` - Tuple 工具
- **tuple_for_each/** - 利用折叠表达式遍历 tuple

#### `metaprogramming/factory/` - 模板工厂
- **general_factory/** - 通用工厂模式 + 离线注册

#### `metaprogramming/misc/` - 其他模板技巧
- **calc_array_size/** - 编译期计算数组长度
- **static_crtp/** - 静态 CRTP
- **class_unity/** - 类统一处理
- **map_macro_to_struct/** - 宏映射到结构体
- **data_container/** - 数据容器
- **dt/** - 数据表 (Data Table)
- **bitset/** - 位图实现
- **scope_guard/** - 作用域守卫

---

### `utility/` - 实用工具

#### `utility/string/` - 字符串处理
- **string_split/** - 字符串分割与处理

#### `utility/timer/` - 计时器

#### `utility/para_binding/` - 参数绑定

#### `utility/macro/` - 宏技巧
- **x_macro_patterns/** - X-Macro 模式演示

---

## 🛠️ 构建与使用

### 依赖
- CMake 3.17+
- C++17 (metaprogramming 模块) / C++20 (主项目)
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
./Snippets              # 主项目测试（算法、并发、容器、模式、工具）
./Metaprogramming       # 模板元编程模块测试
```

---

## 🎯 适用场景

- **algorithm/** - 学习经典算法，参考面试题解
- **concurrency/** - 多线程编程工具复用
- **container/** - 高性能数据结构实现
- **pattern/** - 设计模式实践参考
- **metaprogramming/** - 学习 C++ 模板元编程技巧
- **utility/** - 常用工具函数复用

---

## 📄 License

MIT License
