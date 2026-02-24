# 残魂

这是一个基于 **SGF** 开发的游戏项目。

---

## 💻 开发环境要求

在开始开发前，请确保本地已配置好 **CMake (3.25+)** 及对应的编译器环境：

| 操作系统 | 推荐编译器 | 构建工具 | 检查命令 |
| --- | --- | --- | --- |
| **Windows** | **MSVC** (Visual Studio 2022+) | `cmake` / `MSBuild` | `cl` |
| **Linux** | **GCC** (11.0+) | `cmake` / `make` | `gcc --version` |
| **macOS** | **Apple Clang** | `cmake` / `ninja` | `clang --version` |

---

## 🛠 构建流程

请严格按照以下顺序初始化项目，确保子模块完整加载：

```sh
# 1. 克隆仓库及初始化子模块
git clone https://github.com/CDUDDJ/Game_Fragmented_Soul.git
cd zanhun

# 2. 拉取 sgf 引擎最新更新
git submodule update --remote sgf 

# 3. 初始化 sgf 内部依赖 (初次执行耗时较久)
cd sgf
git submodule update --init --recursive
cd ..

# 4. 配置与多线程构建
cmake -B build
cd build
cmake --build . --parallel
```

---

## 🔄 团队协作与 CI 流程

本项目通过 **在线 CI 自动监测** 保证分支健康，严禁将破坏构建的代码推送到公共分支。

### 1. 角色与权限

* **负责人 (Main):** 最终审核 `test -> main` 的 PR。
* **程序组 (Dev):** 负责功能逻辑。推送前需同步 `main` 分支。
* **美术组 (Art):** 负责资产导入，判定修正等。
* **测试组 (Test):** 负责集成测试，是通往 `main` 的唯一入口。

### 2. 自动化 CI 校验

每当发起 Pull Request (PR) 时，云端 CI 会自动触发：

1. **静态检查：** 扫描基础语法错误。
2. **单平台构建：** 在 Windows 环境下尝试编译。
3. **单元测试：** 运行基础单元测试。

> **红灯禁令：** 若 CI 检测未通过（显示为红叉），测试组与维护者将**直接关闭 PR**。请作者在本地修复并重新推送。

### 3. 操作流程

1. **同步：** `git pull origin main` (保持基准最新)。
2. **开发：** 在 `dev` 或 `art` 分支提交并推送到远程。
3. **提审：** 向 **`test` 分支** 发起 PR。
4. **CI 介入：** 等待在线监测通过。
5. **手动测试：** 测试组合并至 `test` 进行实机验证。
6. **合入主干：** 测试组向 **`main` 分支** 提 PR，由维护者最终确认。

---

### 🤖 自动化监测 (CI) 规则
本项目已配置 GitHub Actions，在以下情况会自动触发构建检测：
1. **PR 阶段：** 任何向 `test` 或 `main` 分支发起的 Pull Request。
2. **Push 阶段：** 只有 `test` 和 `main` 分支的代码更新。

**注：** 如果你的 PR 状态显示为 `Action Failed`，请点击详情查看编译日志，修复后再重新提交。

---

## 🚫 注意事项

底层更新后，若本地编译报错，请务必执行 `git submodule update`。