#ifndef CHOOSINGBOX_HPP_INCLUDED
#define CHOOSINGBOX_HPP_INCLUDED
#include "graphics.hpp"
#include "widgets.hpp"
#include <vector>
#include <iostream>

using namespace std;

class ChoosingWidget: public Widget
{
protected:
    bool _nyiljon_e_le;

	int _valasztott;
	vector<string> _mezok;
	bool _gordul_e;
	int _sav_szelesseg;
	int _sav_magassag;
	int _eger_melyik_elemen;
	int _nyilak_melyik_elemen;
	int _mi_az_elso;
	bool _kifer_e_minden_mezo;
	int _mennyi_fer_ki;


public:
	ChoosingWidget(int x, int y, int sx, int sy, vector<string> mezok,int lenyilos_e);
	ChoosingWidget(int x, int y, int sx, int sy, vector<string> mezok, int lenyilashossz, int savmagassag,int lenyilos_e);
	virtual void draw();
	virtual void handle(genv::event ev);
	virtual string getextrainfo();
	virtual bool is_focused();
	virtual bool is_lenyilo_gomb(genv::event ev);
	virtual bool is_selected_lenyilo_menu(genv::event ev);
	virtual bool is_gordul();
	virtual bool is_lenyilos_widget();
	virtual void setfocused();
	void HozzafuzMezok(string text);
	string getvalasztott();
	int getvalasztottszam();

};



#endif // CHOOSINGBOX_HPP_INCLUDED
