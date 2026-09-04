#pragma once
// 命令模式基类：一个"玩家操作" = execute(做) + undo(撤销)
// 它谁都不认识（不 include Player/Map）——只规定"所有命令都能做和撤销"
// 具体命令（放塔/放怪/升级…）各自一个文件，继承这个基类
// 撤销栈存 vector<unique_ptr<Command>>（基类指针），才能装下各种命令
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;   // 做这个操作
    virtual void undo() = 0;      // 撤销它（把 execute 的账还回去）
};
