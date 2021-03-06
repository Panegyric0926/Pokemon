# 1、题目要求
+ 设计宠物小精灵的类，为简化游戏设计，精灵的属性包括种类（力量型：高攻击；肉盾型：高生命值；防御型：高防御；敏捷型：低攻击间隔，共四种）、名字、等级、经验值、攻击力、防御力、生命值、攻击间隔等（以上属性必须，其他属性可自行添加）（基本要求：本游戏中只有上面的4种类型。进一步要求：上述4种类型可以进一步深入划分，比如力量型又可以再细分为：沙瓦朗、火爆猴、腕力等）。
+ 每个精灵初始等级为1，满级15级，每当精灵升级的时候，宠物对应的属性值会有少量增加（主属性增加量相对较多）。
+ 每个精灵有自己独特的攻击方式，如“闪电攻击”，“火焰攻击”等等，请设计一个精灵的基类，并将精灵的攻击方法设为虚方法以方便子类重写。
+ 请写一个测试程序对设计的精灵类的相关属性和方法（包括攻击函数，升级函数等）进行测试。
+ 题目主要考察点：类的继承，对象数据成员设计，成员函数设计。

# 2、小精灵宏观设计
+ 设计小精灵包括以下属性
	+ 种族
	+ 名字
	+ 攻击力
	+ 防御力
	+ 速度（反应攻击间隔）
	+ 等级
	+ 经验值
+ 小精灵的种族包括以下属性
	+ 种族名
	+ 种族类型（高攻击、高防御、高血量、高速度四种）
	+ 种族基础攻击
	+ 种族基础防御
	+ 种族基础血量
	+ 种族基础速度
	+ 种族经验曲线
	+ 种族技能（四个）、每个技能的描述和技能释放次数（PP点）
关于小精灵的技能，设置如下规则：
+ 每个种族的小精灵有四个技能，包括一个普通攻击和三个特殊技能
+ 普通攻击不消耗技能释放次数，即普通攻击可以无限次释放，防止持久战双方没有技能可以释放
+ 小精灵在1级的时候只拥有普通攻击，在5级习得第二个技能，10级习得第三个技能，15级（满级）习得第四个技能
+ 能够对对方造成伤害的技能拥有一定的被闪避几率，此几率和双方小精灵的速度有关
关于小精灵属性的提升：每个小精灵在初始化的时候会首先被赋予其种族的基础属性（即种族基础攻击等等），在每次等级提升的时候属性的增加具有一定的随机性，这就要求后期使用数据库存储小精灵数据的时候需要把小精灵的所有属性都保存在sqlite3数据库中。

# 3、类的设计与实现
## 3.1 预备信息
> 在说明以下内容之前需要知道的信息
定义了dbout作为信息输出，定义了dbin作为信息输入。目前dbout为cout，dbin为cin。

种族类型（也可以称为精灵类型）为枚举量PokemonType，定义了高攻击、高防御、高血量、高速度这四种种族类型。

**pokemon.h/pokemon.cpp**

根据题目要求，设置枚举类型“精灵类型（PokemonType）”，提供四个枚举值ATK/HP/DEF/SPE来表示此类型的精灵的那个属性比较强

在设计的时候使用“速度”代替了“攻击间隔”这一个量

设计基类PokemonBase，用来派生出不同种族的精灵。基类拥有种族名、精灵类型、类型基础攻击、类型基础防御、类型基础血量、类型基础速度、类型经验曲线、种族技能名称、种族技能描述和种族技能PP值。这些属性的访问权限全部设计为protected以便被派生类访问和被基类指针访问

PokemonBase的构造函数需要传入一个参数type，即精灵类型。PokemonBase会根据精灵类型生成类型基础属性，即同类型的精灵的初始属性是相同的

PokemonBase提供了纯虚函数attack使精灵可以发动攻击。dodge函数用来判断闪避

模板类Race为PokemonBase的基类，意为不同的精灵种族。如 `Race<0>` 是小火龙， `Race<1>` 是妙蛙种子。此模板类只需要定义两个函数，一个是构造函数，另一个是来自基类的攻击函数attack

Race类的构造函数会指定此种族的精灵属于哪些类型，比如小火龙种族属于高攻击型，则使用枚举量ATK作为基类PokemonBase的参数。构造函数还会把PokemonBase中没有初始化的属性全部初始化，包括种族名、经验曲线、技能名称、技能描述、技能PP值。

Race类的attack函数则为此种族的每个技能提供了计算公式。

Pokemon类是具体的小精灵类，它包括种族、小精灵名、当前攻击力、当前防御力、当前血量上限、当前速度、当前等级和当前经验值这些属性。因为在战斗中有些属性会临时发生变化，所以还有战斗中血量、战斗中攻击、战斗中防御、战斗中速度和战斗中PP点这五个属性。战斗时的临时属性拥有getter和setter函数，但是非战斗时属性只有getter函数，其值只能通过构造函数或升级函数更改。

Pokemon的构造函数需要一个种族的const引用作为参数，表示这个精灵属于此种族。因为精灵不可能更改种族的属性，所以种族在内部保存为一个const引用。精灵还可以被重命名，如果没有重命名，则默认使用种族名。精灵在生成时会获得一些基础属性，如基础攻击、基础防御等。这些属性还会被附加一些随机因素，使同一种族生成的精灵有不同的属性

关于攻击函数attack，小精灵Pokemon类中的attack用来实现自动战斗和手动战斗的控制相关操作，确定发动哪个技能后调用种族Race的attack函数。模板类Race中的攻击函数定义了此种族的精灵的攻击计算方式与攻击效果。

小精灵的技能会随着等级的增长而获得，初始只有普通攻击kick，5级时获得第二个技能，10级获得第三个技能，15级获得第四个技能。

**battlecontroller.h/battlecontroller.cpp**

当需要实现两只小精灵的战斗时需要构造战斗控制器BattleController。其构造函数的参数为两个小精灵的引用和一个自动战斗标识。构造结束后调用start函数即可开启战斗

战斗时会有两个计时器timer。计时器会从0开始上升，当精灵A的计时器不小于精灵A的速度时，精灵B发动攻击，以此实现速度高的精灵攻击快的效果。

如果两只小精灵的timer同时达到标准，则速度高的小精灵先发动攻击

当存在一只小精灵的血量为0时另一只小精灵获得战斗胜利

## 3.2 种族基类PokemonBase
设计类PokemonBase作为所有精灵种族的基类。

此类包含了上文中精灵种族应该包含的所有属性，但是在初始化的时候不会给全部这些属性都赋值（如种族名、种族技能这些都需要具体构造种族的时候才能够确定），所以PokemonBase把所有属性的访问属性设置成了protected以便子类（即各个种族类）访问与修改。

此类还声明了种族各属性的getter函数，以便基类指针能够访问子类（种族类）中初始化的属性。

此类的构造函数仅需要提供一个参数：种族类型。在此类的构造函数中会先根据种族类型对种族基础攻击、种族基础防御等属性进行初始化。此处的初始化没有添加随机性，所以种族类型相同的精灵在1级的时候拥有完全相同的属性。

此类提供了攻击函数attack。由于两个小精灵的攻击并不会对种族属性造成影响，只会对小精灵的个体战时属性造成影响，所以此函数是一个const函数，且需要提供两个小精灵的非const引用作为参数以便修改两个小精灵的属性。此函数设计为纯虚函数以便子类实现和被外界通过基类指针访问。

## 3.3 种族模板类template Race
模板类Race使用精灵种族编号作为模板参数。如0号种族为` Race<0> `，1号种族为` Race<1> `。此模板类表示了不同的精灵种族，如妙蛙种子、小火龙等。

此类的构造函数首先根据种族类型的不同而调用PokemonBase的构造函数，使种族的数值属性（种族基础攻击力、种族基础防御力等）根据种族类型而确定下来，然后对以下没有在PokemonBase的构造函数中初始化的数据进行初始化：
+ 种族名
+ 种族经验曲线
+ 种族技能名（4个）
+ 种族技能描述（4个）
+ 技能释放次数

此类实现了PokemonBase中声明的纯虚函数attack。在此函数中，首先根据传入的参数skillIndex判断攻击方小精灵使用了哪个技能，每个技能有不同的伤害计算公式或效果，如果技能命中且对方血量为0则返回true表示战斗结束。

## 3.4 小精灵类Pokemon
此类除了包含每个小精灵的个体属性，还要包含小精灵的战时个体属性，因为在战斗中小精灵的某些属性会得到临时性的更改。这些战时个体属性包括：
+ 血量
+ 攻击力
+ 防御力
+ 速度
+ 每个技能的剩余技能释放次数

此类提供了所有属性（包括战时个体属性和普通个体属性）的getter函数，但是仅提供了战时个体属性的setter函数，因为普通个体属性仅能够通过经验获取函数gainExp在判定为升级的情况下被修改。
关于战斗，此类提供了如下函数：
+ restoreAll
	+ 使战时个体属性恢复为普通个体属性，用于战斗前两只精灵的恢复（初始化）
+ attack
	+ 指定另一只Pokemon作为目标进行攻击
	+ 此函数会根据等级和剩余技能释放次数对玩家选择的技能进行判定，如果判定玩家选择了某个剩余技能释放次数不足的技能或某个当前等级无法释放的技能，则会释放普通攻击
	+ 在选择自动战斗时，此函数会随机选择一个符合等级条件且剩余技能释放次数非0的技能进行释放。选择手动战斗时，将使用dbin从控制台进行输入
	+ 此函数仅作为战斗的控制函数，实际的战斗会调用种族的战斗函数进行各属性的计算
+ takeDamage
	+ 减少当前Pokemon的生命值
	+ 如果当前Pokemon的生命值为0则返回false表示此精灵战败
	+ 当参数（精灵应承受的伤害）小于某阈值时，设置伤害为此阈值。防止因对方精灵防御过高而造成的战斗流程缓慢
+ gainExp
	+ 给当前精灵增加经验
	+ 如果精灵升级，返回true
	+ 如果精灵已经满级（15级）则增加经验无效
	+ 内部使用一个循环来实现一次性增加大量经验造成的连续升级的效果
	+ 精灵升级后会在一定浮动范围内增加自己的属性，也会因为自己的种族类型而在某个属性上有更多的增益

每个小精灵可以拥有自己的名字。如果在构造时没有提供小精灵的名字，则小精灵的名字被初始化为种族的名字。

## 3.5 战斗控制器类BattleController
构造函数包括两个小精灵的非const引用和一个自动战斗标志位。

调用函数start后，战斗开始。战斗控制器中的计数器timer将会增加，当达到某个小精灵的速度值时，另一只小精灵应该发起攻击。调用Pokemon的attack函数实现攻击。

如果判定双方应该同时攻击，则速度快的一方优先进行攻击。

当战斗的一方血量为0时战斗结束，start函数结束。

## 3.6 主程序main
主程序首先使用时间函数初始化随机数种子以便后期产生随机数，然后初始化四个种族以便后面初始化小精灵时使用。

初始化小精灵，调用gainExp以测试升级函数的效果。构造BattleController来实现战斗，调用BattleController::start启动战斗即可。

## 3.7 其他细节
目前仅设计了小火龙（高攻击）、妙蛙种子（高血量）、杰尼龟（高防御）、波波（高速度）四个种族。

# 4、具体实现
## 4.1 种族初始化与精灵生成
在tester.cpp中如下代码初始化了四个种族
```
Race<0> race1;
Race<1> race2;
Race<2> race3;
Race<3> race4;
```
四个种族分别为小火龙（高攻击）、妙蛙种子（高血量）、杰尼龟（高防御）和波波（高速度）

初始化所有种族之后即可使用Pokemon类的构造函数来生成一只精灵。构造函数的第一个参数是精灵的种族，第二个参数为精灵的名字。如果没有给出精灵的名字，则默认使用种族名。示例：
```
Pokemon pokemon1(race1, "pokemon1");
Pokemon pokemon2(race2);
```
生成精灵后会看到如下输出：
```
Init pokemon1 from Charmander
Type: High Attack
Atk: 13
Def: 7
MaxHp: 30
Speed: 11
LV: 1
Exp: 0
Skills:
	Name: kick
	Description: simple attack
	PP: infinity
	Name: spark
	Description: ignore opponent's half defence
	PP: 10
	Name: rage
	Description: increase attack
	PP: 3
	Name: fireball
	Description: cause huge damage
	PP: 5
```
## 4.2 升级
此版本仅提供增加宠物经验值的函数（即升级函数），并未给出经验值结算方案。计划将在以后版本设计。

函数Pokemon::gainExp(int count)可以给精灵增加经验值。经验值达到一定值（升级经验曲线）后即可升级。调用一次此函数可以造成多次升级。参数count应为正整数，不符合条件的count会被默认替换为1

示例：使用代码` pokemon1.gainExp(10) `，可以看到如下输出
```
pokemon1 gains 10 exp!
Now pokemon1 has 10 exp
Level Up!
pokemon1's now LV2!
Atk: 10‐>18!
Def: 3‐>5!
MaxHP: 24‐>34!
Speed: 8‐>13!
```
## 4.3 战斗
如果要进行精灵之间的战斗，则需要构造一个战斗控制器BattleController，其构造函数为` BattleController(Pokemon &pokemon1, Pokemon &pokemon2, bool autoFight = true); `，即需要传递两个已经存在的精灵（可以是同一只）。第三个参数为自动战斗标识，默认自动战斗，设置为false的时候也可以手动战斗

构造BattleController之后，使用BattleController::start()即可开启战斗

示例代码：
```
	// BattleController battle(pokemon1, pokemon2);//auto fight
	BattleController battle(pokemon1, pokemon3, false); //manual fight
	battle.start();
```
自动战斗模式下，系统会随机在精灵能够使用的技能中挑选一个释放。自动战斗产生的输出如下：
```
pokemon1 VS pokemon2!
Battle Start!
pokemon1 uses kick!
pokemon2 takes 13 damage!
pokemon2's HP becomes 24
pokemon2 uses kick!
pokemon1 takes 10 damage!
pokemon1's HP becomes 28
pokemon1 uses kick!
pokemon2 takes 12 damage!
pokemon2's HP becomes 12
pokemon1 uses kick!
pokemon2 takes 10 damage!
pokemon2's HP becomes 2
pokemon2 uses kick!
pokemon1 takes 10 damage!
pokemon1's HP becomes 18
pokemon1 uses kick!
pokemon2 takes 12 damage!
pokemon2 is down!
pokemon1 won!
```
手动战斗模式下，玩家可以选择每一步释放哪个技能。关于技能的获取将在下文中提到。手动战斗可以获得如下输出：
```
pokemon1 VS pokemon2!
Battle Start!

pokemon1, your turn!
Choose a skill to attack!
	1: kick simple		attack
	2: spark(10/10)		ignore opponent's half defence
	3: rage( 3/ 3)		increase attack
	4: fireball( 5/ 5)	cause huge damage
Please input a number: 3

pokemon1 uses rage!
pokemon1's Attack +13
pokemon1's Attack becomes 121

pokemon2, your turn!
Choose a skill to attack!
	1: kick simple		attack
	2: spark(10/10)		ignore opponent's half defence
	3: rage( 3/ 3)		increase attack
	4: fireball( 5/ 5)	cause huge damage
Please input a number: 4

pokemon2 uses razor leaf!
pokemon1 takes 82 damage!
pokemon1's HP becomes 48

pokemon1, your turn!
Choose a skill to attack!
	1: kick simple		attack
	2: spark(10/10)		ignore opponent's half defence
	3: rage( 3/ 3)		increase attack
	4: fireball( 5/ 5)	cause huge damage
Please input a number: 4

pokemon1 uses fireball!
pokemon2 takes 157 damage!
pokemon2's HP becomes 67

pokemon2, your turn!
Choose a skill to attack!
	1: kick simple		attack
	2: spark(10/10)		ignore opponent's half defence
	3: rage( 3/ 3)		increase attack
	4: fireball( 5/ 5)	cause huge damage
Please input a number: 3

pokemon2 uses life drain!
pokemon2 restores 46HP!
pokemon2's HP becomes 113

pokemon1 takes 46 damage!
pokemon1's HP becomes 2
pokemon1, your turn!
Choose a skill to attack!
	1: kick simple		attack
	2: spark(10/10)		ignore opponent's half defence
	3: rage( 3/ 3)		increase attack
	4: fireball( 5/ 5)	cause huge damage
Please input a number: 4

pokemon1 uses fireball!
pokemon2 takes 152 damage!
pokemon2 is down!

pokemon1 won!

请按任意键继续. . .
```
可以看到，精灵的技能有释放次数（PP值），每次释放都会减少此技能的PP值。精灵的第一个技能kick为普通攻击，可以无限次释放。技能后面跟着技能描述，玩家可以根据技能描述来选择释放技能。

玩家需要输入一个数字来释放技能。如果出现错误输入则默认释放普通攻击。当一个精灵的血量HP为0时，另一个精灵获得胜利。

# 5、游戏测试
生成小精灵

获取经验与升级

战斗开始

战斗结束