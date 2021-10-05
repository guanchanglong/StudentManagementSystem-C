/*
制作人：关昌隆(代码实现)
		梁博森(图片支持、调试、bug查找)
		张磊(bug查找、调试)
单位：	西安邮电大学-计算机学院
*/
#define _CRT_SECURE_NO_DEPRECATE 0;
#define USES_CONVERSION 0;
#define _CRT_NONSTDC_NO_DEPRECATE 0;
#define _CRT_SECURE_NO_WARNINGS 0;

#include<graphics.h>      // 引用图形库头文件
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <conio.h>
#include<tchar.h>
#include<Windows.h>

/*宏定义*/
#define LENGTH 30				//定义用户名和密码长度


IMAGE welcome;
IMAGE welcom_button;
IMAGE startup;
IMAGE stu1_exit;
IMAGE end;
IMAGE stu1;
IMAGE stu1_return;
IMAGE stu_register;
IMAGE stu_logon;
IMAGE teacher1;
IMAGE tea_register;
IMAGE tea_logon;
IMAGE teacher1_return;
IMAGE stu_button;
IMAGE tea_button;
IMAGE exit_button;
IMAGE tea_returnwelcome;
IMAGE returnstudentmain_button;
IMAGE stu_resetpassword;
IMAGE stu_scoremanagement1;
IMAGE stu_scoremanagement2;
IMAGE stu_schedulemanagement2_return;
IMAGE teacher_resetpassword;
IMAGE teacher_scoremanagement1;
IMAGE teacher_scoremanagement2;
IMAGE createscore;
IMAGE resetscore;
IMAGE teacher_scoremanagement2_return;
IMAGE returnteachermain_button;
IMAGE returnmainmenu_button;
IMAGE delscore;
IMAGE findscore;
IMAGE statisticsscore1;
IMAGE statisticsscore2;
IMAGE fullmarks;
IMAGE failingstudent;
IMAGE teacher_scoreStatistics2_return;
IMAGE descendingdortscore;
IMAGE averagescore;
IMAGE failingstudent_flipoverbutton_nextpage;
IMAGE failingstudent_flipoverbutton_previouspage;
IMAGE fullmarks_flipoverbutton_nextpage;
IMAGE fullmarks_flipoverbutton_previouspage;
IMAGE findscore_flipoverbutton_nextpage;
IMAGE findscore_flipoverbutton_previouspage;
IMAGE stu_findscore_flipoverbutton_previouspage;
IMAGE stu_findscore_flipoverbutton_nextpage;

int StuLogonFlag = 0;		//定义判断学生是否登录的标志变量
int TeaLogonFlag = 0;	//定义判断教师是否登录的标志变量

FILE *fp1, *fp2, *fp3;
char filename1[] = "教师注册资料.txt";
char filename2[] = "学生注册资料.txt";
char filename3[] = "学生成绩.txt";

void MainMenu();
void Stu_SecondMenu();
void Stu_Register();
void Stu_Logon();
void Tea_Register();
void Tea_Logon();
void Tea_SecondMenu();
void Stu_ResetPassword();
void Stu_ScoreManagement();
void Tea_ResetPassword();
void Tea_ScoreManagement();
void Stu_CreateScore();
void Stu_AmendScore();
void Stu_DeleteScore();
void Stu_FindInformation();
void Stu_ScoreStatistics();
void FullMarks();
void FailingStudent();
void DescendingSortScore();
void AverageScore();
void FlipOverMenu();
void FlipOverMenu1();
void FlipOverMenu2();
void PreviousPage_And_NextPage(int page);
void PreviousPage_And_NextPage1(int page);
void PreviousPage_And_NextPage2(int page);
void FlipOverMenu_Tea_ScoreManagement();
void PreviousPageAndNextPage_Tea_ScoreManagement(int page);
void PreviousPageAndNextPage_Stu_SecondMenu(int page);
void FlipOverMenu_Stu_SecondMenu();

typedef struct teacher
{
	wchar_t Namew[LENGTH];		//定义教师用户名
	char Namec[LENGTH];
	wchar_t password1[LENGTH];	//定义教师账户密码
	wchar_t password2[LENGTH];	//定义教师二次输入密码 
	char password[LENGTH];
	struct teacher *next;
}tea;

typedef struct student
{
	wchar_t Namew[LENGTH];					//定义学生用户名
	char Namec[LENGTH];
	wchar_t password1[LENGTH];				//定义学生账户密码
	wchar_t password2[LENGTH];				//定义学生二次输入密码 
	char password[LENGTH];
	int yu;
	int shu;
	int ying;
	int zongfen;
	struct student *next;
}stu;

int page1 = 1, page2 = 1;//倒序
int page3 = 1, page4 = 1;//不及格
int page5 = 1, page6 = 1;//满分
int page7 = 1, page8 = 1;//教师菜单学生查找
int page9 = 1, page10 = 1;//学生菜单学生查找
stu *node5[LENGTH];//学生菜单学生查找
stu *node4[LENGTH];//教师菜单学生查找
stu *node3[LENGTH];//满分
stu *node2[LENGTH];//不及格
stu *node1[LENGTH];//倒序
stu *node[LENGTH];

inline char* UnicodeToAnsi(wchar_t* szStr)	//将宽字节wchar_t*类型转换为窄字节char*类型
{
	//该函数可以映射一个unicode字符串到一个多字节字符串，执行转换的代码页、接收转换字符串、允许额外的控制等操作。
	int nLen = WideCharToMultiByte(CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL);
	if (nLen == 0)
	{
		return NULL;
	}
	char* pResult = new char[nLen];
	WideCharToMultiByte(CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL);
	return pResult;
}

inline wchar_t*UnicodeToAnsi2(char* str)	//将窄字节char*类型转化为宽字节wchar_t*类型		
{
	//一种windows API 函数，该函数映射一个字符串到一个宽字符（unicode）的字符串。
	int nlen = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	if (nlen == 0)
	{
		return NULL;
	}
	wchar_t*pResult = new wchar_t[nlen];
	MultiByteToWideChar(CP_ACP, 0, str, -1, pResult, nlen);
	return pResult;
}

stu *createlink3(void)								//将文件里的信息转换到链表里
{
	fp3 = fopen(filename3, "a+");
	stu *p, *q, *head;
	stu student;
	p = q = (stu*)malloc(sizeof(stu)-4);
	head = p;
	while (fscanf(fp3, "%s %d %d %d %d\n", student.Namec,&student.yu,&student.shu,&student.ying,&student.zongfen) != EOF)
	{
		p = (stu*)malloc(sizeof(stu)-4);
		strcpy(p->Namec, student.Namec);			//strcpy函数可以复制一个字符数组里的内容到另一个字符数组里
		p->yu = student.yu;
		p->shu = student.shu;
		p->ying = student.ying;
		p->zongfen = student.zongfen;
		q->next = p;
		q = p;
	}
	fclose(fp3);
	q->next = NULL;
	return head;
}

stu *createlink2(void)								//将文件里的信息转换到链表里
{
	fp2 = fopen(filename2, "a+");
	stu *p, *q, *head;
	stu student;
	p = q = (stu*)malloc(sizeof(stu)-7);
	head = p;
	while (fscanf(fp2, "%s %s\n", student.Namec, student.password) != EOF)
	{
		p = (stu*)malloc(sizeof(stu)-7);
		strcpy(p->Namec, student.Namec);			//strcpy函数可以复制一个字符数组里的内容到另一个字符数组里
		strcpy(p->password, student.password);
		q->next = p;
		q = p;
	}
	fclose(fp2);
	q->next = NULL;
	return head;
}

tea *createlink1(void)								//将文件里的信息转换到链表里
{
	fp1 = fopen(filename1, "a+");
	tea *p, *q, *head;
	tea teacher;
	p = q = (tea*)malloc(sizeof(tea)-3);
	head = p;
	while (fscanf(fp1, "%s %s\n", teacher.Namec, teacher.password) != EOF)
	{
		p = (tea*)malloc(sizeof(tea)-3);
		strcpy(p->Namec, teacher.Namec);			//strcpy函数可以复制一个字符数组里的内容到另一个字符数组里
		strcpy(p->password, teacher.password);
		q->next = p;
		q = p;
	}
	fclose(fp1);
	q->next = NULL;
	return head;
}


stu *del2(stu*head, char Namec[])			//删除链表节点
{
	stu *p1, *p2;
	p2 = NULL;
	if (head == NULL)										//传入的是空链表
	{
		MessageBox(NULL, _T("数据库里无学生数据"), _T("修改密码"), MB_ICONSTOP | MB_SETFOREGROUND);
		return head;
	}
	p1 = head;
	while (strcmp(p1->Namec, Namec) != 0 && p1->next != NULL)//遍历链表寻找目标值
	{
		p2 = p1;
		p1 = p2->next;
	}
	if (strcmp(p1->Namec, Namec) == 0)
	{
		if (p1 == head)//目标节点为头节点
		{
			head = p1->next;
		}
		else
		{
			p2->next = p1->next;
		}
	}
	return head;
}

tea *del1(tea*head, char Namec[])			//删除链表节点
{
	tea *p1, *p2;
	p2 = NULL;
	if (head == NULL)										//传入的是空链表
	{
		MessageBox(NULL, _T("数据库里无学生数据"), _T("修改密码"), MB_ICONSTOP | MB_SETFOREGROUND);
		return head;
	}
	p1 = head;
	while (strcmp(p1->Namec, Namec) != 0 && p1->next != NULL)//遍历链表寻找目标值
	{
		p2 = p1;
		p1 = p2->next;
	}
	if (strcmp(p1->Namec, Namec) == 0)
	{
		if (p1 == head)//目标节点为头节点
		{
			head = p1->next;
		}
		else
		{
			p2->next = p1->next;
		}
	}
	return head;
}

stu *save3(stu*head)																//链表的保存
{
	fp3 = fopen(filename3, "w+");												//以w+的方式打开文件，将文件里原来的内容清空，写入新的内容
	while (head->next != NULL)
	{
		head = head->next;
		fprintf(fp3, "%s %d %d %d %d\n", head->Namec,head->yu,head->shu,head->ying,head->zongfen);//保存链表到文件里
	}
	fclose(fp3);
	return head;
}

stu *save2(stu*head)																//链表的保存
{
	fp2 = fopen(filename2, "w+");												//以w+的方式打开文件，将文件里原来的内容清空，写入新的内容
	while (head->next != NULL)
	{
		head = head->next;
		fprintf(fp2, "%s %s\n", head->Namec, head->password);//保存链表到文件里
	}
	fclose(fp2);
	return head;
}

tea *save1(tea*head)																//链表的保存
{
	fp1 = fopen(filename1, "w+");												//以w+的方式打开文件，将文件里原来的内容清空，写入新的内容
	while (head->next != NULL)
	{
		head = head->next;
		fprintf(fp1, "%s %s\n", head->Namec, head->password);//保存链表到文件里
	}
	fclose(fp1);
	return head;
}

stu *pop_sort(stu *head)								//链表冒泡排序
{
	stu *q, *p, *tail, *temp;
	tail = NULL;
	q = head;
	while ((head->next->next) != tail)
	{
		p = head->next;
		q = head;
		while (p->next != tail)
		{
			if ((p->zongfen)<(p->next->zongfen))
			{
				q->next = p->next;
				temp = p->next->next;
				p->next->next = p;
				p->next = temp;
				p = q->next;
			}
			p = p->next;
			q = q->next;
		}
		tail = p;
	}
	return head;
}

stu *Node(stu *head,int n)	//储存结构体指针
{
	node[n] = head;
	return node[n];
}

void Welcome()
{
	loadimage(&welcome, L"begin.jpg");		//导入欢迎界面（特别注意：双引号里面不能有空格，要跟图片命名完全一致）
	putimage(0, 0, &welcome);				//显示欢迎界面

	MOUSEMSG msg;							//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();					// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	while (true)							// 主循环,循环监听鼠标信息
	{
		while (MouseHit())					//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();			//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)	//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 232 && msg.x < 498 && msg.y > 478 && msg.y < 543)//鼠标点击退出按钮所在区域
				{
					loadimage(&welcom_button, L"welcome_button.jpg");	//导入按钮特效图片
					putimage(0, 0, &welcom_button);						//显示按钮特效图片
					Sleep(100);											//延时，降低CPU占用率，并且做到点击效果
					MainMenu();											//调用一级主菜单选项函数
				}
			}
		}
	}
}

//一级主菜单(学生端、教师端)
void MainMenu()
{
	loadimage(&startup, L"4.jpg");
	putimage(0, 0, &startup);
	MOUSEMSG msg;
	FlushMouseMsgBuffer();	
	while (true)
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();
			if (WM_LBUTTONDOWN == msg.uMsg)
			{
				if (msg.x > 185 && msg.x < 492 && msg.y > 541 && msg.y < 678)//鼠标点击“学生端”按钮所在区域
				{
					loadimage(&stu_button, L"stu_button.jpg");			//导入按钮特效图片
					putimage(0, 0, &stu_button);						//显示按钮特效图片
					Sleep(100);
					Stu_SecondMenu();								//调用学生端函数
				}
				if (msg.x > 787 && msg.x < 1150 && msg.y > 548 && msg.y < 676)//鼠标点击“教师端”按钮所在区域
				{
					loadimage(&tea_button, L"tea_button.jpg");			//导入按钮特效图片
					putimage(0, 0, &tea_button);						//显示按钮特效图片
					Sleep(100);
					Tea_SecondMenu();							//调用教师端函数
				}
				if (msg.x > 1128 && msg.x < 1293 && msg.y > 28 && msg.y < 75)
				{
					loadimage(&exit_button, L"exit_button.jpg");
					putimage(0, 0, &exit_button);
					Sleep(100);
					loadimage(&end, L"end.jpg");
					putimage(0, 0, &end);
					system("pause");
					exit(0);
				}
			}
		}
	}
}

//二级菜单学生端目录显示
void Stu_SecondMenu()
{
	loadimage(&stu1, L"stu1.jpg");
	putimage(0, 0, &stu1);
	MOUSEMSG msg;
	FlushMouseMsgBuffer();
	while (true)
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();
			if (WM_LBUTTONDOWN == msg.uMsg)
			{
				if (msg.x > 980 && msg.x < 1046 && msg.y > 554 && msg.y < 619)//点击“教师端”按钮所在区域
					Tea_SecondMenu();//调用教师端函数
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//鼠标点击“返回”按钮所在区域
					MainMenu();//调用一级主菜单选项函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 71 && msg.y < 134)//鼠标点击“创建账户”按钮所在区域
					Stu_Register();//调用学生创建账户函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 162 && msg.y < 228)//鼠标点击“学生登录”按钮所在区域
					Stu_Logon();//调用学生登录函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 252 && msg.y < 318)//鼠标点击“修改密码”按钮所在区域
					Stu_ResetPassword();//调用学生修改密码函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 344 && msg.y < 413)//鼠标点击“学生查找、统计成绩”按钮所在区域
				{
					if (StuLogonFlag == 1)//学生已登录
						Stu_ScoreManagement();//调用学生成绩管理函数
					else
						MessageBox(NULL, _T("您还未登录"), _T("学生管理系统"), MB_ICONEXCLAMATION | MB_SETFOREGROUND);
				}
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					loadimage(&stu1_return, L"stu1_return.jpg");
					putimage(0, 0, &stu1_return);
					Sleep(100);
					Welcome();
				}
				if (msg.x>1063 && msg.x<1295 && msg.y>560 && msg.y<658)		//鼠标点击返回教师端
				{
					loadimage(&returnteachermain_button, L"returnteachermain_button.jpg");
					putimage(0, 0, &returnteachermain_button);
					Sleep(100);
					Tea_SecondMenu();
				}
				if (msg.x>725 && msg.x<853 && msg.y>542 && msg.y<655)
				{
					loadimage(&returnmainmenu_button, L"returnmainmenu_button.jpg");
					putimage(0, 0, &returnmainmenu_button);
					Sleep(100);
					MainMenu();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					StuLogonFlag = 0;
					TeaLogonFlag = 0;
					loadimage(&stu1_exit, L"stu1_exit.jpg");
					putimage(0, 0, &stu1_exit);
					Sleep(100);
					loadimage(&end, L"end.jpg");
					putimage(0, 0, &end);
					system("pause");
					exit(0);
				}
			}
		}
	}
}

//二级菜单：学生创建账户
void Stu_Register()
{
	stu student;
	stu student1;
	fp2 = fopen(filename2, "a+");//以追加的方式打开文件

	loadimage(&stu_register, L"stu_register.jpg");//进入学生端创建账户界面
	putimage(0, 0, &stu_register);
	int i;
	do{
		i = 0;
		InputBox(student1.Namew, 10, _T("请输入用户名"));//提示用户输入用户名
		//接下来查找用户信息表中的内容，比较新输入的用户名是否存在，如果存在，系统给出提示
		while (fscanf(fp2, "%s\n", student.Namec) != EOF)
		{
			if (strcmp(student.Namec, UnicodeToAnsi(student1.Namew)) == 0)
			{
				i++;
				MessageBox(NULL, _T("该用户已经存在，请重新输入"), _T("创建账户"), MB_ICONSTOP | MB_SETFOREGROUND);//输出提示，提醒用户
				break;	//跳出while循环
			}
		}
		if (i == 0)		//说明没有找到重复的用户名 
			break;
	} while (1);		//如果用户名重复则一直循环，直到不重复时跳出循环 
	//输入用户名函数结束 
	//设置密码操作
	do{
		InputBox(student1.password1, 7, _T("请设置6位数密码"));//提示用户输入密码
		InputBox(student1.password2, 7, _T("请确认密码"));//提示用户确认密码
		if (wcscmp(student1.password1, student1.password2) != 0)//两次输入密码不相等 
			MessageBox(NULL, _T("两次输入不一致，请重新输入"), _T("创建账户"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
		{
			MessageBox(NULL, _T("注册成功！"), _T("创建账户"), MB_SETFOREGROUND);
			fprintf(fp2, "%s %s\n", UnicodeToAnsi(student1.Namew),UnicodeToAnsi(student1.password2));//文件保存
			break;
		}
	} while (1);
	fclose(fp2);
}

void Stu_Logon()
{
	stu student;
	loadimage(&stu_logon, L"stu_logon.jpg");//进入学生端学生登录界面
	putimage(0, 0, &stu_logon);

	int i;
	wchar_t username[LENGTH];//定义一个临时存储用户名的字符数组 
	wchar_t password[LENGTH];//定义一个临时存储密码的字符数组 
	do{
		i = 0;
		fp2 = fopen(filename2, "a+");
		InputBox(username, 10, _T("请输入用户名"));//提示用户输入用户名，输入给临时存储用户名的字符数组
		while (fscanf(fp2, "%s\n", student.Namec) != EOF)
		{
			if (strcmp(UnicodeToAnsi(username), student.Namec) == 0)//读取用户名
			{
				i++;
				break;
			}
		}
		if (i==0)//说明没有找到对应用户名 
			MessageBox(NULL, _T("该用户不存在"), _T("学生登录"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;//找到了此用户名，退出输入用户名的循环，进入输入密码模块 
		fclose(fp2);
	} while (1);
	//输入密码
	int j, k = 3;
	do {
		j = 0;
		fp2 = fopen(filename2, "a+");
		InputBox(password, 7, _T("请输入6位密码"));//提示用户输入密码，输入给临时存储密码的字符数组
		while (fscanf(fp2, "%s\n", student.password) != EOF)
		{
			if (strcmp(UnicodeToAnsi(password), student.password) == 0)//读取密码
			{
				j++;
				MessageBox(NULL, _T("登录成功！"), _T("学生登录"), MB_SETFOREGROUND);
				StuLogonFlag = 1;//标志着已经成功登录 
				break;
			}
		}
		if (j != 0)
		{
			break;
		}
		if (j == 0)
		{
			MessageBox(NULL, _T("密码错误"), _T("学生登录"), MB_ICONSTOP | MB_SETFOREGROUND);
			k--;
		}
		if (k == 0)
		{
			break;
		}
		fclose(fp2);
	} while (1);
}


//二级菜单：学生修改密码
void Stu_ResetPassword()
{
	stu student, *head;
	loadimage(&stu_resetpassword, L"stu_resetpassword.jpg");//进入学生端修改密码界面
	putimage(0, 0, &stu_resetpassword);

	int i;
	wchar_t username[LENGTH];
	wchar_t password[LENGTH];
	wchar_t resetpassword[LENGTH];//定义一个临时存储修改后密码的字符数组 
	do {
		i = 0;
		fp2 = fopen(filename2, "a+");
		InputBox(username, 10, _T("请输入用户名"));					//提示用户输入用户名，输入给临时存储用户名的字符数组
		while (fscanf(fp2, "%s\n", student.Namec) != EOF)
		{
			if (strcmp(UnicodeToAnsi(username), student.Namec) == 0)//读取用户名
			{
				i++;
				break;
			}
		}
		if (i==0)													//说明没有找到对应用户名 
			MessageBox(NULL, _T("该用户不存在"), _T("修改密码"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;
		fclose(fp2);
	} while (1);
	fclose(fp2);
	int j, k = 3;
	do {
		j = 0;
		fp2 = fopen(filename2, "a+");
		InputBox(password, 7, _T("请输入原始密码"));
		while (fscanf(fp2, "%s\n", student.password) != EOF)
		{
			if (strcmp(UnicodeToAnsi(password), student.password) == 0)//读取密码
			{
				j++;
				InputBox(resetpassword, 7, _T("密码正确，请输入6位数修改密码"));
				MessageBox(NULL, _T("修改密码成功！"), _T("修改密码"), MB_SETFOREGROUND);
				fclose(fp2);
				head = del2(createlink2(), UnicodeToAnsi(username));		//将文件转入链表，并且删除原有的用户信息
				stu *head1 = head, *p1;
				while (head1->next != NULL)
				{
					head1 = head1->next;
				}
				p1 = (stu*)malloc(sizeof(stu)-7);
				p1->next=NULL;
				strcpy(p1->Namec, UnicodeToAnsi(username));
				strcpy(p1->password, UnicodeToAnsi(resetpassword));
				head1->next = p1;											//将修改后的用户信息放进链表
				save2(head);												//将链表里的信息重新写入文件
				break;
			}
		}
		if (j != 0)
		{
			break;
		}
		if (j == 0)
		{
			MessageBox(NULL, _T("密码错误"), _T("修改密码"), MB_ICONSTOP | MB_SETFOREGROUND);
			k--;
		}
		if (k == 0)
		{
			break;
		}
	} while (1);
}

//二级菜单：学生成绩查询
void Stu_ScoreManagement()
{
	loadimage(&stu_scoremanagement1, L"stu_scoremanagement1.jpg");
	putimage(0, 0, &stu_scoremanagement1);
	stu student, *head, *p, *q, *head1;
	p = q = (stu*)malloc(sizeof(stu)-5);
	head = p;
	int m = 0, m1 = 1;
	int position_x = 430;
	int position_y = 80;
	char yu[LENGTH];
	char shu[LENGTH];
	char ying[LENGTH];
	setbkmode(TRANSPARENT);
	settextcolor(COLORREF(RGB(0, 0, 0)));
	settextstyle(30, 0, _T("楷体"));
	char sequencenum[100];
	wchar_t username[LENGTH];
	InputBox(username, 5, _T("请输入需要查找的学生姓名："));
	outtextxy(position_x, position_y, _T("序号     姓名     高数     离散     大学英语"));
	fp3 = fopen(filename3, "a+");
	while (fscanf(fp3, "%s %d %d %d %d\n", student.Namec, &student.yu, &student.shu, &student.ying, &student.zongfen) != EOF)
	{
		if (strstr(student.Namec, UnicodeToAnsi(username)) != NULL)
		{
			p = (stu*)malloc(sizeof(stu)-5);
			strcpy(p->Namec, student.Namec);
			p->yu = student.yu;
			p->shu = student.shu;
			p->ying = student.ying;
			q->next = p;
			q = p;
		}
	}
	q->next = NULL;
	head1 = head;
	page9 = 1;
	while (head1 != NULL)
	{
		head1 = head1->next;
		if (m1 == 1)
		{
			node5[page9] = head1;
		}
		if (m1 % 9 == 0)
		{
			page9++;
			node5[page9] = head1;
		}
		m1++;
	}
	head = head->next;
	while (head != NULL)
	{
		m++;
		itoa(head->yu, yu, 10);
		itoa(head->shu, shu, 10);
		itoa(head->ying, ying, 10);
		sprintf(sequencenum, "%d", m);
		position_y += 35;
		outtextxy(445, position_y, UnicodeToAnsi2(sequencenum));
		outtextxy(555, position_y, UnicodeToAnsi2(head->Namec));
		outtextxy(700, position_y, UnicodeToAnsi2(yu));
		outtextxy(842, position_y, UnicodeToAnsi2(shu));
		outtextxy(1010, position_y, UnicodeToAnsi2(ying));
		head = head->next;
		if (m == 8)
		{
			break;
		}
	}
	if (m == 8)
	{
		page10 = 1;
		FlipOverMenu_Stu_SecondMenu();
	}
	if (m == 0)
	{
		MessageBox(NULL, _T("教师未添加该学生入数据库"), _T("学生查找"), MB_ICONSTOP | MB_SETFOREGROUND);
	}
	fclose(fp3);
}

void FlipOverMenu_Stu_SecondMenu()		//学生端的翻页菜单
{
	MOUSEMSG msg;
	FlushMouseMsgBuffer();
	while (true)
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();
			if (WM_LBUTTONDOWN == msg.uMsg)
			{
				if (msg.x > 980 && msg.x < 1046 && msg.y > 554 && msg.y < 619)//点击“教师端”按钮所在区域
					Tea_SecondMenu();//调用教师端函数
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//鼠标点击“返回”按钮所在区域
					MainMenu();//调用一级主菜单选项函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 71 && msg.y < 134)//鼠标点击“创建账户”按钮所在区域
					Stu_Register();//调用学生创建账户函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 162 && msg.y < 228)//鼠标点击“学生登录”按钮所在区域
					Stu_Logon();//调用学生登录函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 252 && msg.y < 318)//鼠标点击“修改密码”按钮所在区域
					Stu_ResetPassword();//调用学生修改密码函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 344 && msg.y < 413)//鼠标点击“学生查找、统计成绩”按钮所在区域
				{
					if (StuLogonFlag == 1)//学生已登录
						Stu_ScoreManagement();//调用学生成绩管理函数
					else
						MessageBox(NULL, _T("您还未登录"), _T("学生管理系统"), MB_ICONEXCLAMATION | MB_SETFOREGROUND);
				}
				if (page10>0 && msg.x>491 && msg.x<678 && msg.y>443 && msg.y<503)//上一页
				{
					if (page10 <= 1)
						MessageBox(NULL, _T("已经是第一页"), _T("学生查找"), MB_ICONSTOP | MB_SETFOREGROUND);
					else
					{
						page10--;
						loadimage(&stu_scoremanagement1, L"stu_scoremanagement1.jpg");
						putimage(0, 0, &stu_scoremanagement1);
						Sleep(100);
						loadimage(&stu_findscore_flipoverbutton_previouspage, L"stu_findscore_flipoverbutton_previouspage.jpg");
						putimage(0, 0, &stu_findscore_flipoverbutton_previouspage);
						PreviousPageAndNextPage_Stu_SecondMenu(page10);
					}
				}
				if (page10 <= page9 && msg.x>723 && msg.x<929 && msg.y>420 && msg.y<503)//下一页
				{
					if (page10 == page9)
						MessageBox(NULL, _T("已经是最后一页"), _T("学生查找"), MB_ICONSTOP | MB_SETFOREGROUND);
					else
					{
						page10++;
						loadimage(&stu_scoremanagement1, L"stu_scoremanagement1.jpg");
						putimage(0, 0, &stu_scoremanagement1);
						Sleep(100);
						loadimage(&stu_findscore_flipoverbutton_nextpage, L"stu_findscore_flipoverbutton_nextpage.jpg");
						putimage(0, 0, &stu_findscore_flipoverbutton_nextpage);
						PreviousPageAndNextPage_Stu_SecondMenu(page10);
					}
				}
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					loadimage(&stu1_return, L"stu1_return.jpg");
					putimage(0, 0, &stu1_return);
					Sleep(100);
					Welcome();
				}
				if (msg.x>1063 && msg.x<1295 && msg.y>560 && msg.y<658)		//鼠标点击返回教师端
				{
					loadimage(&returnteachermain_button, L"returnteachermain_button.jpg");
					putimage(0, 0, &returnteachermain_button);
					Sleep(100);
					Tea_SecondMenu();
				}
				if (msg.x>725 && msg.x<853 && msg.y>542 && msg.y<655)		//鼠标点击回到主菜单
				{
					loadimage(&returnmainmenu_button, L"returnmainmenu_button.jpg");
					putimage(0, 0, &returnmainmenu_button);
					Sleep(100);
					MainMenu();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					StuLogonFlag = 0;
					TeaLogonFlag = 0;
					loadimage(&stu1_exit, L"stu1_exit.jpg");
					putimage(0, 0, &stu1_exit);
					Sleep(100);
					loadimage(&end, L"end.jpg");
					putimage(0, 0, &end);
					system("pause");
					exit(0);
				}
			}
		}
	}
}

void PreviousPageAndNextPage_Stu_SecondMenu(int page)	//翻页学生端查找翻页
{
	stu *head = node5[page];
	int m;
	if (page == 1)
		m = 0;
	else
		m = (page - 1) * 8;
	int position_x = 430;
	int position_y = 80;
	char yu[LENGTH];
	char shu[LENGTH];
	char ying[LENGTH];
	setbkmode(TRANSPARENT);
	settextcolor(COLORREF(RGB(0, 0, 0)));
	settextstyle(30, 0, _T("楷体"));
	outtextxy(position_x, position_y, _T("序号     姓名     高数     离散     大学英语"));
	char sequencenum[100];
	while (head != NULL)
	{
		m++;
		itoa(head->yu, yu, 10);
		itoa(head->shu, shu, 10);
		itoa(head->ying, ying, 10);
		sprintf(sequencenum, "%d", m);
		position_y += 35;
		outtextxy(445, position_y, UnicodeToAnsi2(sequencenum));
		outtextxy(555, position_y, UnicodeToAnsi2(head->Namec));
		outtextxy(700, position_y, UnicodeToAnsi2(yu));
		outtextxy(842, position_y, UnicodeToAnsi2(shu));
		outtextxy(1010, position_y, UnicodeToAnsi2(ying));
		head = head->next;
		if (m % 8 == 0)
		{
			break;
		}
	}
}

//第二级教师菜单
void Tea_SecondMenu()
{
	loadimage(&teacher1, L"teacher1.jpg");
	putimage(0, 0, &teacher1);

	MOUSEMSG msg;
	FlushMouseMsgBuffer();
	while (true) 
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();
			if (WM_LBUTTONDOWN == msg.uMsg)
			{
				if (msg.x > 408 && msg.x < 554 && msg.y > 474 && msg.y < 619)//鼠标点击“学生端”按钮所在区域
				{
					loadimage(&returnstudentmain_button, L"returnstudentmain_button.jpg");
					putimage(0, 0, &returnstudentmain_button);
					Sleep(100);
					Stu_SecondMenu();//调用学生端函数
				}
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//鼠标点击“学生端”按钮所在区域
				{
					loadimage(&tea_returnwelcome, L"tea_returnwelcome.jpg");
					putimage(0, 0, &tea_returnwelcome);
					Sleep(100);
					MainMenu();//调用一级主菜单函数
				}
				if (msg.x > 81 && msg.x < 365 && msg.y > 69 && msg.y < 135)//鼠标点击“创建账户”按钮所在区域
					Tea_Register();//调用教师创建账户函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 162 && msg.y < 227)//鼠标点击“教师登录”按钮所在区域
					Tea_Logon();//调用教师登录函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 254 && msg.y < 320)//鼠标点击“修改密码”按钮所在区域
					Tea_ResetPassword();//调用教师修改密码函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 347 && msg.y < 410)//鼠标点击“管理学生成绩”按钮所在区域
				{
					if (TeaLogonFlag == 1)//已登录
					{
						loadimage(&teacher_scoremanagement1, L"teacher_scoremanagement1.jpg");
						putimage(0, 0, &teacher_scoremanagement1);
						Sleep(100);
						Tea_ScoreManagement();//调用教师对学生成绩管理函数
					}
					else
						MessageBox(NULL, _T("您还未登录"), _T("学生管理系统"), MB_ICONEXCLAMATION | MB_SETFOREGROUND);
				}
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					loadimage(&teacher1_return, L"teacher1_return.jpg");
					putimage(0, 0, &teacher1_return);
					Sleep(100);
					Welcome();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					StuLogonFlag = 0;
					TeaLogonFlag = 0;
					loadimage(&stu1_exit, L"teacher1_exit.jpg");
					putimage(0, 0, &stu1_exit);
					Sleep(100);
					loadimage(&end, L"end.jpg");
					putimage(0, 0, &end);
					system("pause");
					exit(0);
				}
			}
		}
	}
}

//教师注册
void Tea_Register()
{
	tea teacher;
	tea teacher1;
	fp1 = fopen(filename1, "a+");//以追加的方式打开文件

	loadimage(&tea_register, L"teacher_register.jpg");//进入学生端创建账户界面
	putimage(0, 0, &tea_register);
	int i;
	do{
		i = 0;
		InputBox(teacher1.Namew, 10, _T("请输入用户名"));
		while (fscanf(fp1, "%s\n", teacher.Namec) != EOF)
		{
			if (strcmp(teacher.Namec, UnicodeToAnsi(teacher1.Namew)) == 0)
			{
				i++;
				MessageBox(NULL, _T("该用户已经存在，请重新输入"), _T("创建账户"), MB_ICONSTOP | MB_SETFOREGROUND);//输出提示，提醒用户
				break;	//跳出while循环
			}
		}
		if (i == 0)		//说明没有找到重复的用户名 
			break;
	} while (1);		//如果用户名重复则一直循环，直到不重复时跳出循环 


	//设置密码
	do{
		InputBox(teacher1.password1, 7, _T("请设置6位数密码"));//提示用户输入密码
		InputBox(teacher1.password2, 7, _T("请确认密码"));//提示用户确认密码
		if (wcscmp(teacher1.password1, teacher1.password2) != 0)//两次输入密码不相等 
			MessageBox(NULL, _T("两次输入不一致，请重新输入"), _T("创建账户"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
		{
			MessageBox(NULL, _T("注册成功！"), _T("创建账户"), MB_SETFOREGROUND);
			fprintf(fp1, "%s %s\n", UnicodeToAnsi(teacher1.Namew), UnicodeToAnsi(teacher1.password2));//文件保存
			break;
		}
	} while (1);
	fclose(fp1);
}

void Tea_Logon()	//教师登录
{
	tea teacher;
	loadimage(&tea_logon, L"teacher_logon.jpg");
	putimage(0, 0, &tea_logon);
	int i;
	wchar_t username[LENGTH];
	wchar_t password[LENGTH];
	do{
		i = 0;
		fp1 = fopen(filename1, "a+");
		InputBox(username, 10, _T("请输入用户名"));
		while (fscanf(fp1, "%s\n", teacher.Namec) != EOF)
		{
			if (strcmp(UnicodeToAnsi(username), teacher.Namec) == 0)//读取密码
			{
				i++;
				break;
			}
		}
		if (i == 0)//说明没有找到对应用户名 
			MessageBox(NULL, _T("该用户不存在"), _T("教师登录"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;//找到了此用户名，退出输入用户名的循环，进入输入密码模块 
		fclose(fp1);
	} while (1);
	//输入密码
	int j, k = 3;
	do {
		j = 0;
		fp1 = fopen(filename1, "a+");
		InputBox(password, 7, _T("请输入6位密码"));
		while (fscanf(fp1, "%s\n", teacher.password) != EOF)
		{
			if (strcmp(UnicodeToAnsi(password), teacher.password) == 0)//读取密码
			{
				j++;
				MessageBox(NULL, _T("登录成功！"), _T("教师登录"), MB_SETFOREGROUND);
				TeaLogonFlag = 1;//标志教师用户登录成功 
				break;
			}
		}
		if (j != 0)
		{
			break;
		}
		if (j == 0)
		{
			MessageBox(NULL, _T("密码错误"), _T("学生登录"), MB_ICONSTOP | MB_SETFOREGROUND);
			k--;
		}
		if (k == 0)
		{
			break;
		}
		fclose(fp1);
	} while (1);
}

//二级菜单：教师修改密码
void Tea_ResetPassword()
{
	tea teacher, *head;
	loadimage(&teacher_resetpassword, L"teacher_resetpassword.jpg");//进入学生端修改密码界面
	putimage(0, 0, &teacher_resetpassword);
 
	int i;
	wchar_t username[LENGTH];
	wchar_t password[LENGTH];
	wchar_t resetpassword[LENGTH];
	do {
		i = 0;
		fp1 = fopen(filename1, "a+");
		InputBox(username, 10, _T("请输入用户名"));
		while (fscanf(fp1, "%s\n", teacher.Namec) != EOF)
		{
			if (strcmp(UnicodeToAnsi(username), teacher.Namec) == 0)//读取用户名
			{
				i++;
				break;
			}
		}
		if (i == 0)													//说明没有找到对应用户名 
			MessageBox(NULL, _T("该用户不存在"), _T("修改密码"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;
		fclose(fp1);
	} while (1);
	fclose(fp1);
	int j, k = 3;
	do {
		j = 0;
		fp1 = fopen(filename1, "a+");
		InputBox(password, 7, _T("请输入原始密码"));
		while (fscanf(fp1, "%s\n", teacher.password) != EOF)
		{
			if (strcmp(UnicodeToAnsi(password), teacher.password) == 0)//读取密码
			{
				j++;
				InputBox(resetpassword, 7, _T("密码正确，请输入6位数修改密码"));
				MessageBox(NULL, _T("修改密码成功！"), _T("修改密码"), MB_SETFOREGROUND);
				fclose(fp1);
				head = del1(createlink1(), UnicodeToAnsi(username));		//将文件转入链表，并且删除原有的用户信息
				tea *head1 = head, *p1;
				while (head1->next != NULL)
				{
					head1 = head1->next;
				}
				p1 = (tea*)malloc(sizeof(tea)-3);
				p1->next = NULL;
				strcpy(p1->Namec, UnicodeToAnsi(username));
				strcpy(p1->password, UnicodeToAnsi(resetpassword));
				head1->next = p1;											//将修改后的用户信息放进链表
				save1(head);												//将链表里的信息重新写入文件
				break;
			}
		}
		if (j != 0)
		{
			break;
		}
		if (j == 0)
		{
			MessageBox(NULL, _T("密码错误"), _T("修改密码"), MB_ICONSTOP | MB_SETFOREGROUND);
			k--;
		}
		if (k == 0)
		{
			break;
		}
	} while (1);
}

//学生管理菜单(教师端)
void Tea_ScoreManagement()
{
	loadimage(&teacher_scoremanagement2, L"teacher_scoremanagement2.jpg");
	putimage(0, 0, &teacher_scoremanagement2);
	MOUSEMSG msg;
	FlushMouseMsgBuffer();
	while (true)
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();
			if (WM_LBUTTONDOWN == msg.uMsg)
			{
				if (msg.x > 68 && msg.x < 314 && msg.y > 69 && msg.y < 146)//鼠标点击“增添学生成绩”按钮所在区域
				{
					Stu_CreateScore();//调用增添学生成绩函数
				}
				if (msg.x > 59 && msg.x < 314 && msg.y > 149 && msg.y < 231)//鼠标点击“修改学生成绩”按钮所在区域
					Stu_AmendScore();//调用教师修改学生成绩函数
				if (msg.x > 62 && msg.x < 314 && msg.y > 231 && msg.y < 319)//鼠标点击“删除学生成绩”按钮所在区域
					Stu_DeleteScore();//调用教师删除学生成绩函数
				if (msg.x > 62 && msg.x < 314 && msg.y > 319 && msg.y < 404)//查找学生信息
					Stu_FindInformation();
				if (msg.x > 62 && msg.x < 314 && msg.y > 404 && msg.y < 476)//统计学生成绩
					Stu_ScoreStatistics();
				if (msg.x > 62 && msg.x < 314 && msg.y > 476 && msg.y < 623)//鼠标点击返回按钮
				{
					loadimage(&teacher_scoremanagement2_return, L"teacher_scoremanagement2_return.jpg");
					putimage(0, 0, &teacher_scoremanagement2_return);
					Sleep(100);
					Tea_SecondMenu();//调用二级菜单教师端
				}
			}
		}
	}
}

void Stu_CreateScore()				//增添学生成绩信息
{
	loadimage(&createscore, L"createscore.jpg");
	putimage(0, 0, &createscore);
	stu student;
	int m = 0;
	wchar_t Name[LENGTH];
	wchar_t yu[LENGTH];
	wchar_t shu[LENGTH];
	wchar_t ying[LENGTH];
	InputBox(Name, 5, _T("学生姓名"));
	fp3 = fopen(filename3, "a+");
	while (fscanf(fp3, "%s\n", student.Namec) != EOF)
	{
		if (strcmp(student.Namec, UnicodeToAnsi(Name)) == 0)
		{
			m++;
			MessageBox(NULL, _T("已有该学生！"), _T("学生成绩添加"), MB_ICONSTOP | MB_SETFOREGROUND);
		}
	}
	if (m == 0)
	{
		InputBox(yu, 4, _T("高数成绩(满分100)"));
		InputBox(shu, 4, _T("离散成绩(满分100)"));
		InputBox(ying, 4, _T("大学英语成绩(满分100)"));
		MessageBox(NULL, _T("添加成功!"), _T("学生添加"), MB_SETFOREGROUND);
		student.zongfen = atoi(UnicodeToAnsi(yu)) + atoi(UnicodeToAnsi(shu)) + atoi(UnicodeToAnsi(ying));
		fprintf(fp3, "%s %d %d %d %d\n", UnicodeToAnsi(Name), atoi(UnicodeToAnsi(yu)), atoi(UnicodeToAnsi(shu)), atoi(UnicodeToAnsi(ying)), student.zongfen);//atoi()函数可以将字符串转换为整型数
		char sequencenum[10];
		sprintf(sequencenum, "%d", 1);
		int position_x = 580;	//“序号”横坐标
		int position_y = 27;	//“序号”纵坐标
		setbkmode(TRANSPARENT);	//设置字体背景为透明
		settextcolor(COLORREF(RGB(0, 0, 0)));	//设置字体颜色为黑色
		settextstyle(40, 0, _T("楷体"));		//设置字体大小，格式楷体
		outtextxy(position_x, position_y, _T("序号   姓名   高数   离散   大学英语"));//显示表格第一行表头
		position_y += 45;//向下推一行
		outtextxy(600, position_y, UnicodeToAnsi2(sequencenum));//显示序号
		outtextxy(712, position_y, Name);						//姓名
		outtextxy(865, position_y, yu);
		outtextxy(1018, position_y, shu);
		outtextxy(1200, position_y, ying);
	}
	fclose(fp3);
}

void Stu_AmendScore()			//学生成绩修改函数
{
	loadimage(&resetscore, L"resetscore.jpg");
	putimage(0, 0, &resetscore);

	wchar_t Name[LENGTH];
	wchar_t yu[LENGTH];
	wchar_t shu[LENGTH];
	wchar_t ying[LENGTH];
	char yu2[LENGTH];
	char shu2[LENGTH];
	char ying2[LENGTH];
	int m = 0;
	char sequencenum[10];
	stu student, *head;
	sprintf(sequencenum, "%d", 1);
	int position_x = 580;
	int position_y = 27;
	setbkmode(TRANSPARENT);	//设置字体背景为透明
	settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
	settextstyle(40, 0, _T("楷体"));//设置字体大小，格式楷体
	fp3 = fopen(filename3, "a+");
	InputBox(Name, 5, _T("请输入需要修改成绩学生的姓名"));
	while (fscanf(fp3, "%s %d %d %d %d\n", student.Namec,&student.yu,&student.shu,&student.ying,&student.zongfen) != EOF)
	{
		if (strcmp(student.Namec, UnicodeToAnsi(Name)) ==0 )
		{
			itoa(student.yu, yu2, 10);
			//char *itoa(int value, char *str, int base);
			//int value 被转换的整数，char *string 转换后储存的字符数组，int radix 转换进制数，如2, 8, 10, 16 进制等，大小应在2 - 36之间。
			itoa(student.shu, shu2, 10);
			itoa(student.ying, ying2, 10);
			outtextxy(position_x, position_y, _T("序号   姓名   高数   离散   大学英语"));//显示表格第一行表头
			position_y += 45;											//向下推一行
			outtextxy(600, position_y, UnicodeToAnsi2(sequencenum));	//序号
			outtextxy(712, position_y, Name);							//姓名
			outtextxy(865, position_y, UnicodeToAnsi2(yu2));
			outtextxy(1018, position_y, UnicodeToAnsi2(shu2));
			outtextxy(1200, position_y, UnicodeToAnsi2(ying2));
			m++;
		}
	}
	if (m == 0)
	{
		MessageBox(NULL, _T("无该学生！"), _T("学生成绩修改"), MB_ICONSTOP | MB_SETFOREGROUND);
	}
	else
	{
		InputBox(yu, 4, _T("请重新输入高数成绩(满分100)"));
		InputBox(shu, 4, _T("请重新输入离散成绩(满分100)"));
		InputBox(ying, 4, _T("请重新输入大学英语成绩(满分100)"));
		head = del2(createlink3()->next, UnicodeToAnsi(Name));		//将文件转入链表，并且删除原有的用户信息
		stu *head1 = head, *p1;
		while (head1->next != NULL)
		{
			head1 = head1->next;
		}
		p1 = (stu*)malloc(sizeof(stu)-4);
		p1->next = NULL;
		strcpy(p1->Namec, UnicodeToAnsi(Name));
		p1->yu = atoi(UnicodeToAnsi(yu));
		p1->shu = atoi(UnicodeToAnsi(shu));
		p1->ying = atoi(UnicodeToAnsi(ying));
		p1->zongfen = atoi(UnicodeToAnsi(yu)) + atoi(UnicodeToAnsi(shu)) + atoi(UnicodeToAnsi(ying));	//三科总分
		head1->next = p1;										//将修改后的用户信息放进链表
		save3(head);											//将链表里的信息重新写入文件
		MessageBox(NULL, _T("修改成功！"), _T("学生成绩修改"), MB_SETFOREGROUND);
		loadimage(&resetscore, L"resetscore.jpg");
		putimage(0, 0, &resetscore);
		position_x = 580;
		position_y = 27;
		outtextxy(position_x, position_y, _T("序号   姓名   高数   离散   大学英语"));//显示表格第一行表头
		position_y += 45;
		outtextxy(600, position_y, UnicodeToAnsi2(sequencenum));
		outtextxy(712, position_y, Name);
		outtextxy(865, position_y, yu);
		outtextxy(1018, position_y, shu);
		outtextxy(1200, position_y, ying);
	}
	fclose(fp3);
}

void Stu_DeleteScore()			//学生信息删除函数
{
	loadimage(&delscore, L"delscore.jpg");
	putimage(0, 0, &delscore);

	wchar_t Name[LENGTH];//定义一个"姓名"字符数组
	char yu2[LENGTH];
	char shu2[LENGTH];
	char ying2[LENGTH];
	int m = 0;
	char sequencenum1[10];
	stu student, *head;
	sprintf(sequencenum1, "%d", 1);
	int position_x = 580;
	int position_y = 27;
	setbkmode(TRANSPARENT);
	settextcolor(COLORREF(RGB(0, 0, 0)));
	settextstyle(40, 0, _T("楷体"));
	fp3 = fopen(filename3, "a+");
	InputBox(Name, 5, _T("请输入需要删除学生的姓名"));
	while (fscanf(fp3, "%s %d %d %d %d\n", student.Namec, &student.yu, &student.shu, &student.ying,&student.zongfen) != EOF)
	{
		if (strcmp(student.Namec, UnicodeToAnsi(Name)) == 0)
		{
			itoa(student.yu, yu2, 10);
			itoa(student.shu, shu2, 10);
			itoa(student.ying, ying2, 10);
			outtextxy(position_x, position_y, _T("序号   姓名   高数   离散   大学英语"));//显示表格第一行表头
			position_y += 45;//向下推一行
			outtextxy(600, position_y, UnicodeToAnsi2(sequencenum1));//显示序号
			outtextxy(712, position_y, Name);//姓名
			outtextxy(865, position_y, UnicodeToAnsi2(yu2));//成绩
			outtextxy(1018, position_y, UnicodeToAnsi2(shu2));//成绩
			outtextxy(1200, position_y, UnicodeToAnsi2(ying2));//成绩
			m++;
		}
	}
	if (m == 0)
	{
		MessageBox(NULL, _T("无该学生！"), _T("学生删除"), MB_ICONSTOP | MB_SETFOREGROUND);
	}
	else
	{
		head = del2(createlink3()->next, UnicodeToAnsi(Name));		//将文件转入链表，并且删除原有的用户信息
		save3(head);											//将链表里的信息重新写入文件
		MessageBox(NULL, _T("删除成功！"), _T("学生删除"), MB_SETFOREGROUND);
		loadimage(&delscore, L"delscore.jpg");
		putimage(0, 0, &delscore);
	}
	fclose(fp3);
}

void Stu_FindInformation()				//查找学生
{
	loadimage(&findscore, L"findscore.jpg");
	putimage(0, 0, &findscore);

	stu student, *head, *p, *q, *head1;
	p = q = (stu*)malloc(sizeof(stu)-5);
	head = p;
	int m = 0, m1 = 1;
	int position_x = 580;
	int position_y = 27;
	char yu[LENGTH];
	char shu[LENGTH];
	char ying[LENGTH];
	setbkmode(TRANSPARENT);
	settextcolor(COLORREF(RGB(0, 0, 0)));
	settextstyle(40, 0, _T("楷体"));
	char sequencenum[100];
	wchar_t username[LENGTH];
	InputBox(username, 5, _T("请输入需要查找的学生姓名："));
	outtextxy(position_x, position_y, _T("序号   姓名   高数   离散   大学英语"));
	fp3 = fopen(filename3, "a+");
	while (fscanf(fp3, "%s %d %d %d %d\n", student.Namec, &student.yu, &student.shu, &student.ying,&student.zongfen) != EOF)
	{
		if (strstr(student.Namec, UnicodeToAnsi(username)) != NULL)
		{
			p = (stu*)malloc(sizeof(stu)-5);
			strcpy(p->Namec, student.Namec);
			p->yu = student.yu;
			p->shu = student.shu;
			p->ying = student.ying;
			q->next = p;
			q = p;
		}
	}
	q->next = NULL;
	head1 = head;
	page7 = 1;
	while (head1 != NULL)
	{
		head1 = head1->next;
		if (m1 == 1)
		{
			node4[page7] = head1;
		}
		if (m1 % 14 == 0)
		{
			page7++;
			node4[page7] = head1;
		}
		m1++;
	}
	head = head->next;
	while (head != NULL)
	{
		m++;
		itoa(head->yu, yu, 10);
		itoa(head->shu, shu, 10);
		itoa(head->ying, ying, 10);
		sprintf(sequencenum, "%d", m);
		position_y += 45;
		outtextxy(600, position_y, UnicodeToAnsi2(sequencenum));
		outtextxy(712, position_y, UnicodeToAnsi2(head->Namec));
		outtextxy(865, position_y, UnicodeToAnsi2(yu));
		outtextxy(1018, position_y, UnicodeToAnsi2(shu));
		outtextxy(1200, position_y, UnicodeToAnsi2(ying));
		head = head->next;
		if (m == 13)
		{
			break;
		}
	}
	if (m == 13)
	{
		page8 = 1;
		FlipOverMenu_Tea_ScoreManagement();
	}
	if (m == 0)
	{
		MessageBox(NULL, _T("没有该学生"), _T("学生查找"), MB_ICONSTOP | MB_SETFOREGROUND);
	}
	fclose(fp3);
}

void FlipOverMenu_Tea_ScoreManagement()
{
	MOUSEMSG msg;
	FlushMouseMsgBuffer();
	while (true)
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();
			if (WM_LBUTTONDOWN == msg.uMsg)
			{
				if (msg.x > 68 && msg.x < 314 && msg.y > 69 && msg.y < 146)//鼠标点击“增添学生成绩”按钮所在区域
				{
					Stu_CreateScore();//调用增添学生成绩函数
				}
				if (msg.x > 59 && msg.x < 314 && msg.y > 149 && msg.y < 231)//鼠标点击“修改学生成绩”按钮所在区域
					Stu_AmendScore();//调用教师修改学生成绩函数
				if (msg.x > 62 && msg.x < 314 && msg.y > 231 && msg.y < 319)//鼠标点击“删除学生成绩”按钮所在区域
					Stu_DeleteScore();//调用教师删除学生成绩函数
				if (msg.x > 62 && msg.x < 314 && msg.y > 319 && msg.y < 404)//查找学生信息
					Stu_FindInformation();
				if (msg.x > 62 && msg.x < 314 && msg.y > 404 && msg.y < 476)//统计学生成绩
					Stu_ScoreStatistics();
				if (page8>0 && msg.x>402 && msg.x<552 && msg.y>60 && msg.y<113)//上一页
				{
					if (page8 <= 1)
						MessageBox(NULL, _T("已经是第一页"), _T("学生查找"), MB_ICONSTOP | MB_SETFOREGROUND);
					else
					{
						page8--;
						loadimage(&findscore, L"findscore.jpg");
						putimage(0, 0, &findscore);
						Sleep(100);
						loadimage(&findscore_flipoverbutton_previouspage, L"findscore_flipoverbutton_previouspage.jpg");
						putimage(0, 0, &findscore_flipoverbutton_previouspage);
						PreviousPageAndNextPage_Tea_ScoreManagement(page8);
					}
				}
				if (page8 <= page7 && msg.x>402 && msg.x<554 && msg.y>139 && msg.y<203)//下一页
				{
					if (page8 == page7)
						MessageBox(NULL, _T("已经是最后一页"), _T("学生查找"), MB_ICONSTOP | MB_SETFOREGROUND);
					else
					{
						page8++;
						loadimage(&findscore, L"findscore.jpg");
						putimage(0, 0, &findscore);
						Sleep(100);
						loadimage(&findscore_flipoverbutton_nextpage, L"findscore_flipoverbutton_nextpage.jpg");
						putimage(0, 0, &findscore_flipoverbutton_nextpage);
						PreviousPageAndNextPage_Tea_ScoreManagement(page8);
					}
				}
				if (msg.x > 62 && msg.x < 314 && msg.y > 476 && msg.y < 623)//鼠标点击返回按钮
				{
					loadimage(&teacher_scoremanagement2_return, L"teacher_scoremanagement2_return.jpg");
					putimage(0, 0, &teacher_scoremanagement2_return);
					Sleep(100);
					Tea_SecondMenu();//调用二级菜单教师端
				}
			}
		}
	}
}

void PreviousPageAndNextPage_Tea_ScoreManagement(int page)//统计学生信息菜单里的上下翻页(查找)
{
	stu *head = node4[page];
	int m;
	if (page == 1)
		m = 0;
	else
		m = (page - 1) * 13;
	int position_x = 580;
	int position_y = 27;
	char yu[LENGTH];
	char shu[LENGTH];
	char ying[LENGTH];
	setbkmode(TRANSPARENT);
	settextcolor(COLORREF(RGB(0, 0, 0)));
	settextstyle(40, 0, _T("楷体"));
	outtextxy(position_x, position_y, _T("序号   姓名   高数   离散   大学英语"));
	char sequencenum[100];
	while (head != NULL)
	{
		m++;
		itoa(head->yu, yu, 10);
		itoa(head->shu, shu, 10);
		itoa(head->ying, ying, 10);
		sprintf(sequencenum, "%d", m);
		position_y += 45;
		outtextxy(600, position_y, UnicodeToAnsi2(sequencenum));
		outtextxy(710, position_y, UnicodeToAnsi2(head->Namec));
		outtextxy(865, position_y, UnicodeToAnsi2(yu));
		outtextxy(1020, position_y, UnicodeToAnsi2(shu));
		outtextxy(1200, position_y, UnicodeToAnsi2(ying));
		head = head->next;
		if (m % 13 == 0)
		{
			break;
		}
	}
}

void Stu_ScoreStatistics()			//学生成绩统计
{
	loadimage(&statisticsscore1, L"statisticsscore1.jpg");
	putimage(0, 0, &statisticsscore1);
	Sleep(100);
	loadimage(&statisticsscore2, L"statisticsscore2.jpg");
	putimage(0, 0, &statisticsscore2);
	MOUSEMSG msg;
	FlushMouseMsgBuffer();
	while (true)
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();
			if (WM_LBUTTONDOWN == msg.uMsg)
			{
				if (msg.x > 74 && msg.x < 277 && msg.y > 89 && msg.y < 166)//鼠标点击“单科满分者”按钮所在区域
					FullMarks();
				if (msg.x > 74 && msg.x < 277 && msg.y > 166 && msg.y < 250)//鼠标点击“不及格者”按钮所在区域
					FailingStudent();
				if (msg.x > 74 && msg.x < 277 && msg.y > 250 && msg.y < 340)//鼠标点击“按成绩总分降序排序”按钮所在区域
					DescendingSortScore();
				if (msg.x>74 && msg.x<277 && msg.y>340 && msg.y<403)//"平均分"按钮
					AverageScore();
				if (msg.x > 74 && msg.x < 277 && msg.y > 505 && msg.y < 580)//鼠标点击返回按钮
				{
					loadimage(&teacher_scoreStatistics2_return, L"teacher_scoreStatistics2_return.jpg");
					putimage(0, 0, &teacher_scoreStatistics2_return);
					Sleep(100);
					Tea_ScoreManagement();
				}
			}
		}
	}
}

void FullMarks()			//显示单科满分的学生
{
	loadimage(&fullmarks, L"fullmarks.jpg");
	putimage(0, 0, &fullmarks);

	stu student, *head, *p, *q, *head1;
	p = q = (stu*)malloc(sizeof(stu)-5);
	head = p;
	int m = 0, m1 = 1;
	int position_x = 580;
	int position_y = 27;
	char yu[LENGTH];
	char shu[LENGTH];
	char ying[LENGTH];
	setbkmode(TRANSPARENT);
	settextcolor(COLORREF(RGB(0, 0, 0)));
	settextstyle(40, 0, _T("楷体"));
	char sequencenum[100];
	outtextxy(position_x, position_y, _T("序号   姓名   高数   离散   大学英语"));
	fp3 = fopen(filename3, "a+");
	while (fscanf(fp3, "%s %d %d %d %d\n", student.Namec, &student.yu, &student.shu, &student.ying,&student.zongfen) != EOF)
	{
		if (student.yu==100||student.shu==100||student.ying==100)
		{
			p = (stu*)malloc(sizeof(stu)-5);
			strcpy(p->Namec, student.Namec);
			p->yu = student.yu;
			p->shu = student.shu;
			p->ying = student.ying;
			q->next = p;
			q = p;
		}
	}
	q->next = NULL;
	head1 = head;
	page5 = 1;
	while (head1 != NULL)
	{
		head1 = head1->next;
		if (m1 == 1)
		{
			node3[page5] = head1;
		}
		if (m1 % 15 == 0)
		{
			page5++;
			node3[page5] = head1;
		}
		m1++;
	}
	while (head != NULL)
	{
		m++;
		head = head->next;
		itoa(head->yu, yu, 10);
		itoa(head->shu, shu, 10);
		itoa(head->ying, ying, 10);
		sprintf(sequencenum, "%d", m);
		position_y += 45;
		outtextxy(600, position_y, UnicodeToAnsi2(sequencenum));
		outtextxy(710, position_y, UnicodeToAnsi2(head->Namec));
		outtextxy(865, position_y, UnicodeToAnsi2(yu));
		outtextxy(1020, position_y, UnicodeToAnsi2(shu));
		outtextxy(1200, position_y, UnicodeToAnsi2(ying));
		if (m == 14)
		{
			break;
		}
	}
	if (m == 14)
	{
		page6 = 1;
		FlipOverMenu();
	}
	if (m == 0)
	{
		MessageBox(NULL, _T("没有单科满分的学生"), _T("学生统计"), MB_ICONSTOP | MB_SETFOREGROUND);
	}
	fclose(fp3);
}

void FailingStudent()				//显示不及格的学生
{
	loadimage(&failingstudent, L"failingstudent.jpg");
	putimage(0, 0, &failingstudent);

	stu student, *head, *p, *q, *head1;
	p = q = (stu*)malloc(sizeof(stu)-5);
	head = p;
	int m = 0,m1 = 1;
	int position_x = 580;
	int position_y = 27;
	char yu[LENGTH];
	char shu[LENGTH];
	char ying[LENGTH];
	setbkmode(TRANSPARENT);
	settextcolor(COLORREF(RGB(0, 0, 0)));
	settextstyle(40, 0, _T("楷体"));
	char sequencenum[100];
	outtextxy(position_x, position_y, _T("序号   姓名   高数   离散   大学英语"));
	fp3 = fopen(filename3, "a+");
	while (fscanf(fp3, "%s %d %d %d %d\n", student.Namec, &student.yu, &student.shu, &student.ying,&student.zongfen) != EOF)
	{
		if (student.yu < 60 || student.shu < 60 || student.ying < 60)
		{
			p = (stu*)malloc(sizeof(stu)-5);
			strcpy(p->Namec, student.Namec);
			p->yu = student.yu;
			p->shu = student.shu;
			p->ying = student.ying;
			q->next = p;
			q = p;
		}
	}
	q->next = NULL;
	head1 = head;
	page3 = 1;
	while (head1 != NULL)
	{
		head1 = head1->next;
		if (m1 == 1)
		{
			node2[page3] = head1;
		}
		if (m1 % 15 == 0)
		{
			page3++;
			node2[page3] = head1;
		}
		m1++;
	}
	while (head != NULL)
	{
		m++;
		head = head->next;
		itoa(head->yu, yu, 10);
		itoa(head->shu, shu, 10);
		itoa(head->ying, ying, 10);
		sprintf(sequencenum, "%d", m);
		position_y += 45;
		outtextxy(600, position_y, UnicodeToAnsi2(sequencenum));
		outtextxy(710, position_y, UnicodeToAnsi2(head->Namec));
		outtextxy(865, position_y, UnicodeToAnsi2(yu));
		outtextxy(1020, position_y, UnicodeToAnsi2(shu));
		outtextxy(1200, position_y, UnicodeToAnsi2(ying));
		if (m == 14)
		{
			break;
		}
	}
	if (m == 14)
	{
		page4 = 1;
		FlipOverMenu1();
	}
	if (m == 0)
	{
		MessageBox(NULL, _T("没有不及格的学生"), _T("学生统计"), MB_ICONSTOP | MB_SETFOREGROUND);
	}
	fclose(fp3);
}

void DescendingSortScore()		//降序排列
{
	loadimage(&descendingdortscore, L"descendingdortscore.jpg");
	putimage(0, 0, &descendingdortscore);

	stu *head, *head1, *head2;
	head = createlink3();
	head1 = pop_sort(head);		//进行链表降序排序，返回头节点
	head1 = head1->next;
	head2 = head1;
	int m = 0, m1 = 1;
	int position_x = 580;
	int position_y = 27;
	char yu[LENGTH];
	char shu[LENGTH];
	char ying[LENGTH];
	char zongfen[LENGTH];
	setbkmode(TRANSPARENT);
	settextcolor(COLORREF(RGB(0, 0, 0)));
	settextstyle(30, 0, _T("楷体"));
	char sequencenum[100];
	outtextxy(position_x, position_y, _T("序号    姓名    高数    离散    英语   三科总分"));
	page1 = 1;
	while (head2!= NULL)
	{
		if (m1 == 1)
		{
			node1[page1] = head2;
		}
		head2 = head2->next;
		if (m1 % 18 == 0)
		{
			page1++;
			node1[page1] = head2;
		}
		m1++;
	}
	while (head1!=NULL)
	{
		m++;
		itoa(head1->yu, yu, 10);
		itoa(head1->shu, shu, 10);
		itoa(head1->ying, ying, 10);
		itoa(head1->zongfen, zongfen, 10);
		sprintf(sequencenum, "%d", m);
		position_y += 35;
		outtextxy(600, position_y, UnicodeToAnsi2(sequencenum));
		outtextxy(680, position_y, UnicodeToAnsi2(head1->Namec));
		outtextxy(825, position_y, UnicodeToAnsi2(yu));
		outtextxy(945, position_y, UnicodeToAnsi2(shu));
		outtextxy(1070, position_y, UnicodeToAnsi2(ying));
		outtextxy(1200, position_y, UnicodeToAnsi2(zongfen));
		head1 = head1->next;
		if (m == 18)
		{
			break;
		}
	}
	if (m == 18)
	{
		page2 = 1;
		FlipOverMenu2();
	}
	if (m == 0)
	{
		MessageBox(NULL, _T("数据库里未添加学生"), _T("学生统计"), MB_ICONSTOP | MB_SETFOREGROUND);
	}
}

void AverageScore()			//显示学生各科的平均分
{
	loadimage(&averagescore, L"averagescore.jpg");
	putimage(0, 0, &averagescore);
	int count = 0;
	double x = 0, y1 = 0, y2 = 0, y3 = 0, y4 = 0;
	double yu, shu, ying, zongfen;
	char yu2[LENGTH];
	char shu2[LENGTH];
	char ying2[LENGTH];
	char zongfen2[LENGTH];
	stu *head;
	head = createlink3();
	while (head->next != NULL)
	{
		head = head->next;
		y1 = y1 + head->yu;
		y2 = y2 + head->shu;
		y3 = y3 + head->ying;
		y4 = y4 + head->zongfen;
		count = count + 1;	//count代表学生人数
	}
	yu = y1/ count;			//平均分
	shu = y2 / count;
	ying = y3 / count;
	zongfen = y4 / count;
	sprintf(yu2, "%.1lf", yu);
	sprintf(shu2, "%.1lf", shu);
	sprintf(ying2, "%.1lf", ying);
	sprintf(zongfen2, "%.1lf", zongfen);
	int position_x = 580;
	int position_y = 35;
	setbkmode(TRANSPARENT);
	settextcolor(COLORREF(RGB(0, 0, 0)));
	settextstyle(25, 0, _T("楷体"));
	outtextxy(position_x, position_y, _T("高数平均分   离散平均分   英语平均分   三科总平均分"));
	position_y += 40;
	outtextxy(600, position_y, UnicodeToAnsi2(yu2));
	outtextxy(790, position_y, UnicodeToAnsi2(shu2));
	outtextxy(950, position_y, UnicodeToAnsi2(ying2));
	outtextxy(1115, position_y, UnicodeToAnsi2(zongfen2));
}

void FlipOverMenu()		//统计学生信息菜单里满分的翻页菜单
{
	MOUSEMSG msg;
	FlushMouseMsgBuffer();
	while (true)
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();
			if (WM_LBUTTONDOWN == msg.uMsg)
			{
				if (msg.x > 74 && msg.x < 277 && msg.y > 89 && msg.y < 166)//鼠标点击“单科满分者”按钮所在区域
					FullMarks();
				if (msg.x > 74 && msg.x < 277 && msg.y > 166 && msg.y < 250)//鼠标点击“不及格者”按钮所在区域
					FailingStudent();
				if (msg.x > 74 && msg.x < 277 && msg.y > 250 && msg.y < 340)//鼠标点击“按成绩总分降序排序”按钮所在区域
					DescendingSortScore();
				if (msg.x>74 && msg.x<277 && msg.y>340 && msg.y<403)//"平均分"按钮
					AverageScore();
				if (page6>0 && msg.x>478 && msg.x<558 && msg.y>155 && msg.y<317)//上一页
				{
					if (page6 <= 1)
						MessageBox(NULL, _T("已经是第一页"), _T("学生统计"), MB_ICONSTOP | MB_SETFOREGROUND);
					else
					{
						page6--;
						loadimage(&fullmarks, L"fullmarks.jpg");
						putimage(0, 0, &fullmarks);
						Sleep(100);
						loadimage(&fullmarks_flipoverbutton_previouspage, L"fullmarks_flipoverbutton_previouspage.jpg");
						putimage(0, 0, &fullmarks_flipoverbutton_previouspage);
						PreviousPage_And_NextPage(page6);
					}
				}
				if (page6 <= page5 && msg.x>478 && msg.x<558 && msg.y>352 && msg.y<514)//下一页
				{
					if (page6 == page5)
						MessageBox(NULL, _T("已经是最后一页"), _T("学生统计"), MB_ICONSTOP | MB_SETFOREGROUND);
					else
					{
						page6++;
						loadimage(&fullmarks, L"fullmarks.jpg");
						putimage(0, 0, &fullmarks);
						Sleep(100);
						loadimage(&fullmarks_flipoverbutton_nextpage, L"fullmarks_flipoverbutton_nextpage.jpg");
						putimage(0, 0, &fullmarks_flipoverbutton_nextpage);
						PreviousPage_And_NextPage(page6);
					}
				}
				if (msg.x > 74 && msg.x < 277 && msg.y > 505 && msg.y < 580)//鼠标点击返回按钮
				{
					loadimage(&teacher_scoreStatistics2_return, L"teacher_scoreStatistics2_return.jpg");
					putimage(0, 0, &teacher_scoreStatistics2_return);
					Sleep(100);
					Tea_ScoreManagement();
				}
			}
		}
	}
}

void FlipOverMenu1()		//统计学生信息菜单里不及格的翻页菜单
{
	MOUSEMSG msg;
	FlushMouseMsgBuffer();
	while (true)
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();
			if (WM_LBUTTONDOWN == msg.uMsg)
			{
				if (msg.x > 74 && msg.x < 277 && msg.y > 89 && msg.y < 166)//鼠标点击“单科满分者”按钮所在区域
					FullMarks();
				if (msg.x > 74 && msg.x < 277 && msg.y > 166 && msg.y < 250)//鼠标点击“不及格者”按钮所在区域
					FailingStudent();
				if (msg.x > 74 && msg.x < 277 && msg.y > 250 && msg.y < 340)//鼠标点击“按成绩总分降序排序”按钮所在区域
					DescendingSortScore();
				if (msg.x>74 && msg.x<277 && msg.y>340 && msg.y<403)//"平均分"按钮
					AverageScore();
				if (page4>0 && msg.x>478 && msg.x<558 && msg.y>155 && msg.y<317)//上一页
				{
					if (page4 <= 1)
						MessageBox(NULL, _T("已经是第一页"), _T("学生统计"), MB_ICONSTOP | MB_SETFOREGROUND);
					else
					{
						page4--;
						loadimage(&failingstudent, L"failingstudent.jpg");
						putimage(0, 0, &failingstudent);
						Sleep(100);
						loadimage(&failingstudent_flipoverbutton_previouspage, L"failingstudent_flipoverbutton_previouspage.jpg");
						putimage(0, 0, &failingstudent_flipoverbutton_previouspage);
						PreviousPage_And_NextPage1(page4);
					}
				}
				if (page4 <= page3 && msg.x>478 && msg.x<558 && msg.y>352 && msg.y<514)//下一页
				{
					if (page4 == page3)
						MessageBox(NULL, _T("已经是最后一页"), _T("学生统计"), MB_ICONSTOP | MB_SETFOREGROUND);
					else
					{
						page4++;
						loadimage(&failingstudent, L"failingstudent.jpg");
						putimage(0, 0, &failingstudent);
						Sleep(100);
						loadimage(&failingstudent_flipoverbutton_nextpage, L"failingstudent_flipoverbutton_nextpage.jpg");
						putimage(0, 0, &failingstudent_flipoverbutton_nextpage);
						PreviousPage_And_NextPage1(page4);
					}
				}
				if (msg.x > 74 && msg.x < 277 && msg.y > 505 && msg.y < 580)//鼠标点击返回按钮
				{
					loadimage(&teacher_scoreStatistics2_return, L"teacher_scoreStatistics2_return.jpg");
					putimage(0, 0, &teacher_scoreStatistics2_return);
					Sleep(100);
					Tea_ScoreManagement();
				}
			}
		}
	}
}


void FlipOverMenu2()		//统计学生信息菜单里倒序的翻页菜单
{
	MOUSEMSG msg;
	FlushMouseMsgBuffer();
	while (true)
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();
			if (WM_LBUTTONDOWN == msg.uMsg)
			{
				if (msg.x > 74 && msg.x < 277 && msg.y > 89 && msg.y < 166)//鼠标点击“单科满分者”按钮所在区域
					FullMarks();
				if (msg.x > 74 && msg.x < 277 && msg.y > 166 && msg.y < 250)//鼠标点击“不及格者”按钮所在区域
					FailingStudent();
				if (msg.x > 74 && msg.x < 277 && msg.y > 250 && msg.y < 340)//鼠标点击“按成绩总分降序排序”按钮所在区域
					DescendingSortScore();
				if (msg.x>74 && msg.x<277 && msg.y>340 && msg.y<403)//"平均分"按钮
					AverageScore();
				if (page2>0 && msg.x>360 && msg.x<511 && msg.y>464 && msg.y<538)//上一页
				{
					if (page2<=1)
						MessageBox(NULL, _T("已经是第一页"), _T("学生统计"), MB_ICONSTOP | MB_SETFOREGROUND);
					else
					{
						page2--;
						loadimage(&descendingdortscore, L"descendingdortscore.jpg");
						putimage(0, 0, &descendingdortscore);
						PreviousPage_And_NextPage2(page2);
					}
				}
				if (page2<=page1 && msg.x>372 && msg.x<501 && msg.y>576 && msg.y<654)//下一页
				{
					if (page2==page1)
						MessageBox(NULL, _T("已经是最后一页"), _T("学生统计"), MB_ICONSTOP | MB_SETFOREGROUND);
					else
					{
						page2++;
						loadimage(&descendingdortscore, L"descendingdortscore.jpg");
						putimage(0, 0, &descendingdortscore);
						PreviousPage_And_NextPage2(page2);
					}
				}
				if (msg.x > 74 && msg.x < 277 && msg.y > 505 && msg.y < 580)//鼠标点击返回按钮
				{
					loadimage(&teacher_scoreStatistics2_return, L"teacher_scoreStatistics2_return.jpg");
					putimage(0, 0, &teacher_scoreStatistics2_return);
					Sleep(100);
					Tea_ScoreManagement();
				}
			}
		}
	}
}

void PreviousPage_And_NextPage(int page)//统计学生信息菜单里的上下翻页(满分)
{
	stu *head = node3[page];
	int m;
	if (page == 1)
		m = 0;
	else
		m = (page - 1) * 14;
	int position_x = 580;
	int position_y = 27;
	char yu[LENGTH];
	char shu[LENGTH];
	char ying[LENGTH];
	setbkmode(TRANSPARENT);
	settextcolor(COLORREF(RGB(0, 0, 0)));
	settextstyle(40, 0, _T("楷体"));
	outtextxy(position_x, position_y, _T("序号   姓名   高数   离散   大学英语"));
	char sequencenum[100];
	while (head != NULL)
	{
		m++;
		itoa(head->yu, yu, 10);
		itoa(head->shu, shu, 10);
		itoa(head->ying, ying, 10);
		sprintf(sequencenum, "%d", m);
		position_y += 45;
		outtextxy(600, position_y, UnicodeToAnsi2(sequencenum));
		outtextxy(710, position_y, UnicodeToAnsi2(head->Namec));
		outtextxy(865, position_y, UnicodeToAnsi2(yu));
		outtextxy(1020, position_y, UnicodeToAnsi2(shu));
		outtextxy(1200, position_y, UnicodeToAnsi2(ying));
		head = head->next;
		if (m % 14 == 0)
		{
			break;
		}
	}
}

void PreviousPage_And_NextPage1(int page)//统计学生信息菜单里的上下翻页(不及格)
{
	stu *head = node2[page];
	int m;
	if (page == 1)
		m = 0;
	else
		m = (page - 1) * 14;
	int position_x = 580;
	int position_y = 27;
	char yu[LENGTH];
	char shu[LENGTH];
	char ying[LENGTH];
	setbkmode(TRANSPARENT);
	settextcolor(COLORREF(RGB(0, 0, 0)));
	settextstyle(40, 0, _T("楷体"));
	outtextxy(position_x, position_y, _T("序号   姓名   高数   离散   大学英语"));
	char sequencenum[100];
	while (head != NULL)
	{
		m++;
		itoa(head->yu, yu, 10);
		itoa(head->shu, shu, 10);
		itoa(head->ying, ying, 10);
		sprintf(sequencenum, "%d", m);
		position_y += 45;
		outtextxy(600, position_y, UnicodeToAnsi2(sequencenum));
		outtextxy(710, position_y, UnicodeToAnsi2(head->Namec));
		outtextxy(865, position_y, UnicodeToAnsi2(yu));
		outtextxy(1020, position_y, UnicodeToAnsi2(shu));
		outtextxy(1200, position_y, UnicodeToAnsi2(ying));
		head = head->next;
		if (m % 14 == 0)
		{
			break;
		}
	}
}

void PreviousPage_And_NextPage2(int page)//统计学生信息菜单里的上下翻页(倒序)
{
	stu *head = node1[page];
	int m;
	if (page == 1)
		m = 0;
	else
		m = (page - 1) * 18;
	int position_x = 580;
	int position_y = 27;
	char yu[LENGTH];
	char shu[LENGTH];
	char ying[LENGTH];
	char zongfen[LENGTH];
	setbkmode(TRANSPARENT);
	settextcolor(COLORREF(RGB(0, 0, 0)));
	settextstyle(30, 0, _T("楷体"));
	outtextxy(position_x, position_y, _T("序号    姓名    高数    离散    英语   三科总分"));
	char sequencenum[100];
	while (head != NULL)
	{
		m++;
		itoa(head->yu, yu, 10);
		itoa(head->shu, shu, 10);
		itoa(head->ying, ying, 10);
		itoa(head->zongfen, zongfen, 10);
		sprintf(sequencenum, "%d", m);
		position_y += 35;
		outtextxy(600, position_y, UnicodeToAnsi2(sequencenum));
		outtextxy(680, position_y, UnicodeToAnsi2(head->Namec));
		outtextxy(825, position_y, UnicodeToAnsi2(yu));
		outtextxy(945, position_y, UnicodeToAnsi2(shu));
		outtextxy(1070, position_y, UnicodeToAnsi2(ying));
		outtextxy(1200, position_y, UnicodeToAnsi2(zongfen));
		head = head->next;
		if (m%18==0)
		{
			break;
		}
	}
}

int main()
{
	initgraph(1400, 701);//定义窗口大小
	Welcome();				//程序入口
	return 0;
}