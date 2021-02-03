/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/* Copyright (C) 2021 utoecat
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//includes
#include<iostream>
#include<termios.h>
#include<stdlib.h>
#include<set>
#include<sstream>
#include<iomanip>
#include<cmath>
#include<wchar.h>
#include<wctype.h>

//defines
#define C_D << "\u001b[47m\u001b[30m"
#define C_B << "\u001b[46m\u001b[37m" << endl

//namespace
using namespace std;

//global variables
bool   work = true; //Main Cycle Work Status
double i = 0,i2 = 0,ir = 0; //Main Numbers
char   opr = '+';// Operation Char
int    STAT = 0; // Work Position
string history[5] = {"1","2","3","4","С++ is cool!!!"};//History Array
const char C_SQR = u'\u221a';

//main sets
set<char> mcharSet;
char numChars[] = {'0','1','2','3','4','5','6','7','8','9','.'};
set<char> numSet(numChars,numChars+11);

//Initialize new terminal i/o settings
static struct termios old, new1;
void initTermios(int echo) {
    tcgetattr(0, &old); // grab old terminal i/o settings 
    new1 = old; // make new settings same as old settings 
    new1.c_lflag &= ~ICANON; // disable buffered i/o
    new1.c_lflag &= echo ? ECHO : ~ECHO; // set echo mode 
    tcsetattr(0, TCSANOW, &new1); // use these new terminal i/o settings now 
}

// Restore old terminal i/o settings 
void resetTermios(void) {
    tcsetattr(0, TCSANOW, &old);
}

//Clear terminal space
void clean()
{
cout <<"\u001b[46m\033[1;1H" << endl;
std::system("clear");
}

//Cancel test... If pressed E Main cycle will be stopped
bool doCancelT(char cc)
{
if (cc == 'E' || cc == 'e')
	{
	work = false;
	return true;
	} else return false;
}

//Press any key...
void myPause()
{
char c = 0;
cout << "Press Any key for continue :";
while(c == 0)
	{
	c = std::cin.get();
    }
	doCancelT(c);
}

//Early declaration
void doDraw();

//Number Input Controller
double getNum()
{
	char cch = 0;
	string cach;

	while (!(cch == '\n'))
 {
	if (numSet.set::count(cch))
	{
		cach = cach + cch;
		cout << cch;
	} else if (cch == '\177')
	{
		if (cach.length() > 0) {cach.erase(cach.length()-1,1);
		cout << "\u001b[1D" << ' ' << "\u001b[1D";}
	} else if (cch == '-') 
	{
		if (cach[0] == '-') 
		{
		cach.erase(0,1);
		} else
		{
			cach = '-' + cach;
		}
			cout << "\u001b[1000D" << cach;
	}
	cin.clear();
	cch = std::cin.get();
	if (doCancelT(cch)) {break;}
 }
	return atof(cach.c_str());
}

//Math char Input Controller
char getChr()
{
	char c = '+',r;
	while (!(c == '\n'))
	{
	if (mcharSet.set::count(c) || c == 's' || c == 'S') {
	if (c == 's' || c == 'S') { c = C_SQR;}
	cout << c;
	cin.clear();
	cout << "\u001b[1D";
	r = c;
	}
	c = std::cin.get();
	if (doCancelT(c)) {return '+';}
	}
	return r;
}

//Calculation Function
double calclTe (double i,double i2,char mm)
{
	switch (mm)
	{
	case '+' : return i + i2;
	case '-' : return i - i2;
	case '*' : return i * i2;
	case '%' : return i * i2 / 100;
	case '^' : return pow(i,i2);
	case C_SQR : return i * sqrt(i2);
	case '/' : if (i2 == 0) { return 0; } else { return i / i2;}
	default  : return 0;
	}
}

//Add to history...
void historyAdd (string s)
{
	for (int iii = 3; iii >= 0; iii--)
	{
	history[iii+1] = history[iii];
	}
	history[0] = s;
}

//Draw History
void historyDraw ()
{
 for (int iii = 0; iii < 5; iii++)
	{
	cout C_B << " " C_D << "║┊*" << history[iii];
 	}
}

//Convert Double to String (IN REFRACTORING PROCESS)
string dblToStr (double d)
{
stringstream sstr;
	sstr.unsetf(std::ios_base::floatfield);
	sstr.unsetf(std::ios_base::fixed);
	sstr.unsetf(std::ios_base::scientific);
sstr << d;
return sstr.str();
}

//*********************************************************************


//*********************************************************************
int main ()
{
	initTermios(0); //make mew terminal options
	cout << "\033]0;TCALC - SIMPLE TERMINAL CALCULATOR\007";
	mcharSet.insert('+'); // add chars to set
	mcharSet.insert('-');
	mcharSet.insert('/');
	mcharSet.insert('*');
	mcharSet.insert('%');
	mcharSet.insert('^');
	mcharSet.insert(C_SQR);
	//MAIN CYCLE
	while (work)
	{	
	clean(); // clear screen
	doDraw(); //draw UI
		
	cout << setprecision(15); //:D

	//IF STAT = Show result => calculate result
	if (STAT == 4) {ir = calclTe(i,i2,opr);}

	//draw history
	cout <<"\u001b[8;1000H" C_D ;
	if (STAT != 0 ) {historyDraw ();}

	//draw math expression
	cout <<"\u001b[17;4H" C_D ;
	if (STAT != 0 ) 
		{switch (STAT)
		{
			case 0 : cout << "W E L C O M E ! ! !";break; //WELCOME PAGE
			case 1 : cout << "NULL";break;				  //ENTER FIRST NUM
			case 2 : cout << i << " _ " << 0;break;		  //ENTER math char NUM
			case 3 : cout << i << ' ' << opr << ' ' << 0;break;//ENTER second NUM
			case 4 : cout << i << ' ' << opr << ' ' << i2 << " = " << ir;break;//result
		}}
	cout <<"\u001b[19;4H" C_D ;
	switch (STAT) 
		{
			case 0 : cout <<"\033[22;4H" ;myPause(); STAT++; break;
			case 1 : cout << "Enter first number :";i = getNum(); STAT++; break;
			case 2 : cout << "Enter math char :";opr = getChr(); STAT++; break;
			case 3 : cout << "Enter second number :";i2 = getNum(); STAT++; break;
			case 4 : cout << "RESULT : " << ir C_B << " " C_D << "║#";
					myPause();
					historyAdd(dblToStr(i)+' '+opr+' '+dblToStr(i2)+" = "+dblToStr(ir));
					STAT = 1;
					i = 0;
					i2 = 0;
					ir = 0;
					opr = '_';
					break;
		}
	}

	//When EXIT
	resetTermios(); //reset terminal options to default
	cout << "\u001b[0m"; // reset colors
	cout <<"\033[1;1H" << endl; //goto 0;0 position
	std::system("clear"); // clear terminal
	cout << "thank you for using tcalc!" << endl; // goodbye!
	return 0;//end
}


//DRAW PROCEDURE
void doDraw()
{
// white fill - \u001b[47m  text - \u001b[30m
// blue fill -  \u001b[46m  text - \u001b[37m
cout
<<" *     "  C_D <<"╔═══════════════════════════════════════════╗"                C_B
<<" *     "  C_D <<"║        Simple Terminal Calculator         ║██"              C_B
<<" *     "  C_D <<"║       Version 0.2 (GNU) By UtoECat        ║██"              C_B
<<" *     "  C_D <<"╚═══════════════════════════════════════════╝██"              C_B
<<" *      " C_D <<"██████████████████████████████████████████████"               C_B
<<" "   C_D <<"╔════════════════════════════════════════════════════════╗"   C_B;

if (STAT == 0) 
{
cout<<" "   C_D <<"║                          HELP :                        ║██" C_B
    <<" "   C_D <<"║┌┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┐║██" C_B
<<" "   C_D <<"║┊* Press E or E key to exit. This is simple terminal   ┊║██" C_B
<<" "   C_D <<"║┊* calculator, writed in C++. It can calculate simple  ┊║██" C_B
<<" "   C_D <<"║┊* mathematical expression like X + Y = ... It can аlso┊║██" C_B
<<" "   C_D <<"║┊* multiply, divide , find perchange and other..You can┊║██" C_B
<<" "   C_D <<"║┊* freely copy, distribute and modify this calculator, ┊║██" C_B
<<" "   C_D <<"║┊* provided that you guarantee all these rights to other║██" C_B
<<" "   C_D <<"║┊* users who will use your copy / modification, and you┊║██" C_B
<<" "   C_D <<"║┊* also agree not to alter the authorship of this calc ┊║██" C_B
<<" "   C_D <<"║┊* You can only identify yourself as a developer of a  ┊║██" C_B
<<" "   C_D <<"║┊* modification or a distributor. Learn more about GNU:┊║██" C_B
<<" "   C_D <<"║┊* www.gnu.org/licenses/gpl-3.0.ru.html                ┊║██" C_B
<<" "   C_D <<"║└┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┘║██" C_B
<<" "   C_D <<"║(GNU) By UtoECat 2021 - 2021 :D                         ║██" C_B
<<" "   C_D <<"║Press Any                                               ║██" C_B;
}

else 
{
cout<<" "   C_D <<"║                        HISTORY :                       ║██" C_B
<<" "   C_D <<"║┌┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┐║██" C_B
<<" "   C_D <<"║┊*                                                     ┊║██" C_B
<<" "   C_D <<"║┊*                                                     ┊║██" C_B
<<" "   C_D <<"║┊*                                                     ┊║██" C_B
<<" "   C_D <<"║┊*                                                     ┊║██" C_B
<<" "   C_D <<"║┊*                                                     ┊║██" C_B
<<" "   C_D <<"║└┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┘║██" C_B
<<" "   C_D <<"║Mathematical expression :                               ║██" C_B
<<" "   C_D <<"║┌┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┐║██" C_B
<<" "   C_D <<"║┊                                                      ┊║██" C_B
<<" "   C_D <<"║└┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┘║██" C_B
<<" "   C_D <<"║#                                                       ║██" C_B
<<" "   C_D <<"║#                                                       ║██" C_B
<<" "   C_D <<"║┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄║██" C_B
<<" "   C_D <<"║HINT : Press CTRL + C OR Press (E or E) TO EXIT         ║██" C_B;
}

cout
<<" "   C_D <<"╚════════════════════════════════════════════════════════╝██" C_B
<<"  "  C_D <<"███████████████████████████████████████████████████████████"  << "\u001b[46m\u001b[37m";
}
