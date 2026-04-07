# Git 与 GitHub 上传指南

## 适用范围
本文档用于把当前 `F:\RM\test` 工程纳入 Git 管理，并上传到 GitHub。该工程是 STM32CubeMX + Keil MDK-ARM 项目，建议只提交源码、工程配置和必要文档，不要提交大量编译产物。

## 一、本地初始化 Git

在当前目录打开 PowerShell，执行：

```powershell
git init
git branch -M main
git config user.name "你的名字"
git config user.email "你的邮箱"
```

## 二、先添加 .gitignore

建议先创建 `.gitignore`，避免把 Keil 中间文件和构建输出上传。可忽略以下内容：

```gitignore
MDK-ARM/zero_program/
*.o
*.d
*.map
*.lst
*.htm
*.axf
*.dep
*.crf
*.tmp
JLinkLog.txt
```

如果你只想管理源码，`user_program.bin` 这类二进制文件也建议忽略；如果它是发布产物，再单独保留。

## 三、首次提交
确认需要提交的内容后执行：

```powershell
git add .
git status
git commit -m "init: import stm32 keil project"
```

建议优先保留这些目录和文件：
- `Src/`、`Inc/`、`User/`
- `Drivers/`、`Middlewares/`
- `MDK-ARM/zero_program.uvprojx`
- `zero_program.ioc`
- `AGENTS.md` 与其他说明文档

## 四、上传到 GitHub
先在 GitHub 新建一个空仓库，不要勾选初始化 README。然后关联远程仓库：

```powershell
git remote add origin https://github.com/你的用户名/你的仓库名.git
git push -u origin main
```

如果你已经配置 SSH，也可以改用：

```powershell
git remote add origin git@github.com:你的用户名/你的仓库名.git
git push -u origin main
```

## 五、后续日常操作
本地修改后常用流程：

```powershell
git status
git add .
git commit -m "bsp: adjust gpio mapping"
git push
```

拉取云端更新：

```powershell
git pull --rebase origin main
```

## 六、建议
- 涉及引脚、时钟、外设映射修改时，提交说明里注明是否同步修改了 `zero_program.ioc`。
- 提交前尽量先清理 `MDK-ARM/zero_program/` 下的构建产物。
- 如果后续需要，我可以直接继续帮你补一份适合这个工程的 `.gitignore`，并顺手初始化 Git 仓库。
