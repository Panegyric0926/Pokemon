# 1����ĿҪ��
+ ÿ���û���Ҫע��һ���˺ţ��û���ȫ��Ψһ���������κ������û�����ͬ��Ҫ����ע��ʧ�ܵĳ���ʱ�ķ�����
+ ʵ��ע�ᡢ��¼���ǳ����ܣ������� C/S ģʽ���ͻ��˺ͷ������socket����ͨ�ţ�����˱��������û�����Ϣ��
+ ÿ���û�ӵ�У��û�����ӵ�еľ��飬�������ԡ��û�ע��ɹ�ʱ��ϵͳ�Զ�����ַ�����1��������û���
+ �û����Բ鿴���гɹ�ע���û�ӵ�еľ��飬Ҳ���Բ鿴���е�ǰ���ߵ��û���
+ ��Ŀ��Ҫ����㣺socketͨ�ţ����������������û���Ϣ�洢��ʽ�����潻���������������ӱ��ơ�

# 2���������
�ڵ�һ�׶εĻ����ϣ�ʵ�����¸Ľ���
+ �����û���
+ ʹ�����ݿ�洢��Ϣ
+ ʵ��socket����ͨ��
+ ��ɷ���˽ӿ�
��һ�汾������Ǵ�С�������ʵ�����ֵġ��ڶ��汾��ͬ�����ӷ���˽ӿڵĽǶȿ�ʼ��ƣ���ͬʱ�������ݿ������

������������ʱ������һ����������������״̬��ʹ�ö��̼߳���ʵ�ְ��������ֹͣ������������Hub���������������̺߳���listenFunc��terminateFunc��ǰ������ʵ����������������������ʵ�ְ���ֹͣ��������

��Զ��û���¼�����⣬����������һ��ͳһ�ĵ�¼�˿�A0������˿ڽ�д�����ͻ��˳����С��ͻ��������˵Ķ˿�A0�����¼ʱ������˳��򽫷�����ͻ��û�һ��Ŀǰδ��ʹ�õ�endpoint�˿�Ax���ͻ��˽����Ӵ�Ax�˿���ʵ�ֳ��������ӡ�

�û�����ʽҪ��
+ �������ո񡢻س����Ʊ�ȿհ��ַ�
+ ����6-30
	+ �����ʽҪ��
		+ ��������ĸ�����֡��»���`_`
		+ ����6-30
���ݿ�schema��
```
User(
	id integer primary key,
	name text unique not null,
	password text not null
);
Pokemon(
	id integer primary key,
	userid integer not null,
	name text not null,
	race int not null,
	atk int not null,
	def int not null,
	maxHp int not null,
	speed int not null,
	lv int not null,
	exp int not null,
);
```
��������User��idΪinteger���͵�primary key�Ļ���������sqlite3�Զ�����id

Endpoint��һ��timer�����û�����timerû�и�������������ʱ�������Ͽ����Ӳ�delete Endpoint

��Endpoint����
+ ʹ��vector����Endpoint��ָ�룬ʹ����Endpoints����ͨ���±���ʣ������㴦���ڴ档
+ Endpoint������������timer��ʱ�ҷ���socket�����ѶϿ��������Hub�رմ�Endpoint�����巽�����£�
	+ public Endpoint::start()�����������񲢷��ض˿ںţ��������0���ʾ����ʧ��
	+ public Endpoint::process()��������дsocket��accept����������process�����д���������󣬷���ʱ����endpoint��������ʱ���û��˳���
	+ Hub::mornitor(Endpoint *)���̺߳�����ÿ���½�Endpoint��ʱ���½�һ���̣߳����ô˺���������Ϊ�µ�Endpoint��ָ��
	+ Hub����ʹ��Endpoint::start()��ȡ�˿ںţ�Ȼ���½��̰߳�mornitor����detach��
	+ Hub::mornitor�����е���Endpoint::process()��ʼrecv����process��������ʱ��ʾ��endpoint�������У���Hub��Endpointָ������������˶���delete֮
+ ��ΪHub��mornitor�̺߳�listenFunc�̺߳�������Ҫ����Endpointָ����������������������ֹ���̳߳��ֹ���
ͨ�ŷ�ʽ���ͻ��˷���һ�����󣬷������ظ�һ����Ϣ������˲�������������ͻ��˷���ע������ʱ���������ظ���
Endpoint��������������
+ Endpointʹ�ó�����
+ �ͻ��˶Ͽ�ʱ��recv��������SOCKET_ERROR������onlineΪfalse
+ Endpoint��accept�ɹ�������onlineΪtrue
+ timer��ʱ�����online��Ϊfalse���ж���ҳ�ʱ��δ��½���˳�
+ ���timer��ʱǰ������µ�½����ֹtimer
	+ ʹ��condition_variableʵ�ִ���������sleep
Hub�ṩ�Ľӿڣ�
```
login <username> <password>
logon <username> <password>
```
Endpoint�ṩ�Ľӿڣ�
```
logout
resetPassword <oldPassword> <newPassword>
getPlayerList
getPokemonList [playerID]
getPokemon <pokemonID>
pokemonChangeName <pokemonID> <newName>
```
������أ�
�����ʹ��GB2312���룬�ͻ���ʶ��ʱʹ��` QString QString::fromLocal8Bit(const char *str, int size =-1) `��ʵ���ַ�ת��������ʱ�����Ϣ��������Ҳ��Ҫʹ��`QString.toLocal8Bit`��ʵ��ת�����Դ�ʵ��������Ϣ���ݡ�
Ŀǰ�ܹ��������ĵĵط��У�
+ �û���
+ ������
+ ������

��Ҫ��װLAV filters���ܲ�����Ƶ����Ƶ�ļ�������exeĿ¼�µ�mediaĿ¼��

ʹ��QSSʵ����ʽ�����ݷ��롣ע��QSS�ļ�һ����Ҫʹ��UTF-8���룬����ʹ��ASCII���롣�˴�ʹ����GB2312��