# Pokemon：宠物小精灵对战系统
## 题目一：宠物小精灵的加入
+ 设计宠物小精灵的类，为简化游戏设计，精灵的属性包括种类（力量型：高攻击；肉盾型：高生命值；防御型：高防御；敏捷型：低攻击间隔，共四种）、名字、等级、经验值、攻击力、防御力、生命值、攻击间隔等（以上属性必须，其他属性可自行添加）（基本要求：本游戏中只有上面的4种类型。进一步要求：上述4种类型可以进一步深入划分，比如力量型又可以再细分为：沙瓦朗、火爆猴、腕力等）。
+ 每个精灵初始等级为1，满级15级，每当精灵升级的时候，宠物对应的属性值会有少量增加（主属性增加量相对较多）。
+ 每个精灵有自己独特的攻击方式，如“闪电攻击”，“火焰攻击”等等，请设计一个精灵的基类，并将精灵的攻击方法设为虚方法以方便子类重写。
+ 请写一个测试程序对设计的精灵类的相关属性和方法（包括攻击函数，升级函数等）进行测试。
+ 题目主要考察点：类的继承，对象数据成员设计，成员函数设计。

## 题目二：用户注册与平台登录
+ 每个用户需要注册一个账号，用户名全局唯一，不能有任何两个用户名相同，要考虑注册失败的场景时的反馈。
+ 实现注册、登录、登出功能，均采用 C/S 模式，客户端和服务端用socket进行通信，服务端保存所有用户的信息。
+ 每个用户拥有：用户名、拥有的精灵，两个属性。用户注册成功时，系统自动随机分发三个1级精灵给用户。
+ 用户可以查看所有成功注册用户拥有的精灵，也可以查看所有当前在线的用户。
+ 题目主要考察点：socket通信，交互场景反馈，用户信息存储方式，界面交互，其它合理的新颖设计。

## 题目三：游戏对战的设计
+ 已经登录的在线用户可以和服务器进行虚拟决斗，决斗分两种：升级赛和决斗赛，两种比赛都能增长精灵宠物经验值。服务器上有一个虚拟精灵的列表，用户可以挑选其中任意一个进行比赛（升级赛或者决斗赛）。另外决斗赛中用户胜出可以直接获得该战胜的精灵，失败则系统从用户的精灵中随机选三个（不够三个精灵的情况就选择他所有的精灵），然后由用户选一个送出。
	+ 升级赛只是用户用来增加精灵经验值，规则开发者自定；
	+ 累积多少经验值升一级，规则开发者自定；
	+ 决斗赛的上述规则同升级赛，只是额外还可以赢得一个宠物或失去一个宠物。
+ 用户如果没有精灵（比如总是失败，已经全部送出去），则系统会随机放给他一个初级精灵。
+ 请让你的系统自动模拟每场比赛的每次出招。另外，为了增加不确定性，可以加入概率闪避攻击和暴击伤害机制。
	+ 比赛的过程和结果由系统根据上述规则自动模拟完成，要求结果具有一定的随机性。
+ 用户增加新功能，可以查看某个用户的胜率。
+ 用户增加新属性，为宠物个数徽章（金银铜）和高级宠物徽章（金银铜)。
	+ 分别根据拥有的宠物个数的多少和拥有高级宠物（15级）个数的多少颁发。
+ 题目主要考察点：客户端与服务器数据交互（可采用多进程或异步通信或其他方法均可），并发请求处理，类的方法设计，伤害计算方法设计，界面交互，其它合理的新颖设计。