#include "ChoosingBox.hpp"
#include "graphics.hpp"
#include <sstream>


using namespace genv;


ChoosingWidget::ChoosingWidget(int x, int y, int sx, int sy, vector<string> mezok,int lenyilos_e) :Widget(x,y,sx,sy)
{
    if (lenyilos_e==1)
        _nyiljon_e_le=true;
    else
        _nyiljon_e_le=false;
	_mezok.resize(mezok.size());
	_mezok=mezok;
	_valasztott=0;
	_focused=false;
	if(!_nyiljon_e_le)
        _gordul_e=true;
    else
        _gordul_e=false;
	_kifer_e_minden_mezo=true;
	_sav_magassag=20;
	_mennyi_fer_ki=(700-_y-_size_y)/_sav_magassag;
	_eger_melyik_elemen=-1;
	_nyilak_melyik_elemen=-1;
	_mi_az_elso=0;
	int maxi=_size_x;
	for (unsigned int i=0; i<_mezok.size(); i++) {
		if( gout.twidth(_mezok[i])>maxi)
			maxi=gout.twidth(_mezok[i]);
	}
	_sav_szelesseg=maxi+10;
	if(_x+_sav_szelesseg>700)
		_x=700-_sav_szelesseg-1;
	if(_y==700-1-_size_y) {
		_y=700-_size_y-2*_sav_magassag-3;
		_kifer_e_minden_mezo=false;
		_mennyi_fer_ki=2;
	}

}
ChoosingWidget::ChoosingWidget(int x, int y, int sx, int sy, vector<string> mezok, int lenyilashossz, int savmagassag,int lenyilos_e) :Widget(x,y,sx,sy)
{
     if (lenyilos_e==1)
        _nyiljon_e_le=true;
    else
        _nyiljon_e_le=false;
	_mezok.resize(mezok.size());
	_mezok=mezok;
	_valasztott=0;
	_focused=false;
	if(!_nyiljon_e_le)
        _gordul_e=true;
    else
        _gordul_e=false;

	_sav_magassag=savmagassag;
	if(lenyilashossz>_mezok.size()*_sav_magassag) {
		_kifer_e_minden_mezo=true;
		_mennyi_fer_ki=(700-_y-_size_y)/_sav_magassag;
	} else {
		_kifer_e_minden_mezo=false;
		_mennyi_fer_ki=lenyilashossz/_sav_magassag;
	}

	_eger_melyik_elemen=-1;
	_nyilak_melyik_elemen=-1;
	_mi_az_elso=0;
	int maxi=_size_x;
	for (unsigned int i=0; i<_mezok.size(); i++) {
		if( gout.twidth(_mezok[i])>maxi)
			maxi=gout.twidth(_mezok[i]);
	}
	_sav_szelesseg=maxi+10;
	if(_x+_sav_szelesseg>700)
		_x=700-_sav_szelesseg-1;
	if(_y==700-1-_size_y) {
		_y=700-_size_y-2*_sav_magassag-3;
		_kifer_e_minden_mezo=false;
		_mennyi_fer_ki=2;
	}
}
bool ChoosingWidget::is_lenyilo_gomb(event ev)
{
	return ev.pos_x>_x+_size_x-20 && ev.pos_x<_x+_size_x && ev.pos_y>_y && ev.pos_y<_y+_size_y;
}
bool ChoosingWidget::is_selected_lenyilo_menu(event ev)
{
	if(_kifer_e_minden_mezo)
		return ev.pos_x>=_x && ev.pos_x<=_x+_sav_szelesseg && ev.pos_y>=_y+_size_y && ev.pos_y<=_y+_size_y+_sav_magassag*_mezok.size();
	else
		return ev.pos_x>=_x && ev.pos_x<=_x+_sav_szelesseg && ev.pos_y>=_y+_size_y && ev.pos_y<=_y+_size_y+_sav_magassag*_mennyi_fer_ki;
}
void ChoosingWidget::draw()
{
	canvas nyil;
	canvas nyil2;
	nyil2.open(9,9);
	nyil2<<move_to(0,8)<<color(255,243,233)<<line_to(4,0)<<line_to(8,8);
	nyil.open(9,9);
	nyil<<move_to(0,0)<<color(255,243,233)<<line_to(4,8)<<line_to(8,0);
	gout<<move_to(_x,_y)<<color(255,243,233)<<box(_size_x,_size_y);
	if (!_focused) {
		gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);

		gout<<move_to(_x+_size_x-20,_y)<<color(255,243,233)<<box(20,_size_y);
		gout<<move_to(_x+_size_x-20+2,_y+2)<<color(0,0,0)<<box(20-4,_size_y-4);
	}
	if (_focused) {
		gout << move_to(_x+4, _y+4) << color(0,0,0) << box(_size_x-8, _size_y-8);


		if(_gordul_e) {
			gout<<move_to(_x+_size_x-20,_y)<<color(0,122,223)<<box(20,_size_y);

			if(!_kifer_e_minden_mezo) {
				gout<<move_to(_x+_size_x,_y)<<color(255,243,233)<<box(20,_size_y);
				gout<<move_to(_x+2+_size_x,_y+2)<<color(0,0,0)<<box(20-4,_size_y-4);
				gout<<stamp(nyil,_x+_size_x+5,_y+3*(_size_y/5));
				gout<<stamp(nyil2,_x+_size_x+5,_y+(_size_y/5));
			}
		} else
			gout<<move_to(_x+_size_x-20,_y)<<color(255,243,233)<<box(20,_size_y);
		gout<<move_to(_x+_size_x-20+4,_y+4)<<color(0,0,0)<<box(20-8,_size_y-8);


	}
	if(gout.twidth(_mezok[_valasztott])>_size_x-20-15) {
		string ideiglenes="";
		for (unsigned int i=0; i<_mezok[_valasztott].size(); i++) {
			if(gout.twidth(ideiglenes)<_size_x-20-15)
				ideiglenes.push_back(_mezok[_valasztott][i]);
		}

		gout<<move_to(_x+(_size_x-20)/2-gout.twidth(ideiglenes)/2,_y+_size_y/2+(gout.cascent()+gout.cdescent())/2)<<color(255,243,233)<<text(ideiglenes);

	} else
		gout<<move_to(_x+(_size_x-20)/2-gout.twidth(_mezok[_valasztott])/2,_y+_size_y/2+(gout.cascent()+gout.cdescent())/2)<<color(255,243,233)<<text(_mezok[_valasztott]);

	if(_gordul_e) {

		if(_kifer_e_minden_mezo) {
			for (unsigned int i=0; i<_mezok.size(); i++) {
				gout<<move_to(_x,_y+_size_y+(i-_mi_az_elso)*_sav_magassag)<<color(255,243,233)<<box(_sav_szelesseg+1,_sav_magassag);
				if(_eger_melyik_elemen==-1 && _nyilak_melyik_elemen==-1)
					gout<<move_to(_x+1,_y+1+_size_y+(i-_mi_az_elso)*_sav_magassag+1)<<color(0,0,0)<<box(_sav_szelesseg-2,_sav_magassag-2);
				else {
					bool _mindhamis=true;
					if(_eger_melyik_elemen!=-1 && _nyilak_melyik_elemen!=-1) {
						if(i==_eger_melyik_elemen ) {
							gout<<move_to(_x+1,_y+1+_size_y+(i-_mi_az_elso)*_sav_magassag+1)<<color(0,122,223)<<box(_sav_szelesseg-2,_sav_magassag-2);
							_mindhamis=false;
						}
					}
					if(_eger_melyik_elemen==-1 && _nyilak_melyik_elemen==i) {
						gout<<move_to(_x+1,_y+1+_size_y+(i-_mi_az_elso)*_sav_magassag+1)<<color(0,122,223)<<box(_sav_szelesseg-2,_sav_magassag-2);
						_mindhamis=false;
					}
					if(_eger_melyik_elemen==i&& _nyilak_melyik_elemen==-1) {
						gout<<move_to(_x+1,_y+1+_size_y+(i-_mi_az_elso)*_sav_magassag+1)<<color(0,122,223)<<box(_sav_szelesseg-2,_sav_magassag-2);
						_mindhamis=false;
					}
					if(_mindhamis)
						gout<<move_to(_x+1,_y+1+_size_y+(i-_mi_az_elso)*_sav_magassag+1)<<color(0,0,0)<<box(_sav_szelesseg-2,_sav_magassag-2);


				}


				gout<<move_to(_x+_sav_szelesseg/2-gout.twidth(_mezok[i])/2,_y+_size_y+((i-_mi_az_elso)*_sav_magassag)+10+(gout.cascent()+gout.cdescent())/2)<<color(255,243,233)<<text(_mezok[i]);

			}
			gout<<move_to(_x,_y+_size_y)<<color(255,243,233)<<line_to(_x,_y+_size_y+_mezok.size()*_sav_magassag);
			gout<<move_to(_x+1,_y+_size_y+1)<<color(255,243,233)<<line_to(_x+1,_y+_size_y+_mezok.size()*_sav_magassag+1);

			gout<<move_to(_x,_y+_size_y+_mezok.size()*_sav_magassag)<<line_to(_sav_szelesseg+_x,_y+_size_y+_mezok.size()*_sav_magassag);
			gout<<move_to(_x,_y+_size_y+_mezok.size()*_sav_magassag+1)<<line_to(_sav_szelesseg+_x,_y+_size_y+_mezok.size()*_sav_magassag+1);

		} else {
			gout<<move_to(_x,_y+_size_y)<<color(0,0,0)<<box(_sav_szelesseg+1,_sav_magassag*_mennyi_fer_ki+2);
			canvas kijelzettek;
			kijelzettek.open(_sav_szelesseg,_sav_magassag*_mennyi_fer_ki+10);

			for(unsigned int i=_mi_az_elso; i<_mi_az_elso+_mennyi_fer_ki; i++) {
				kijelzettek<<move_to(0,0+(i-_mi_az_elso)*_sav_magassag)<<color(255,243,233)<<box(_sav_szelesseg,_sav_magassag);
				if(_eger_melyik_elemen!=i && _nyilak_melyik_elemen!=i)
					kijelzettek<<move_to(0+1,0+(i-_mi_az_elso)*_sav_magassag+1)<<color(0,0,0)<<box(_sav_szelesseg-2,_sav_magassag-2);
				else {
					bool _mindhamis=true;
					if(_eger_melyik_elemen!=-1 && _nyilak_melyik_elemen!=-1) {
						if(i==_nyilak_melyik_elemen ) {
							kijelzettek<<move_to(0+1,0+(i-_mi_az_elso)*_sav_magassag+1)<<color(0,0,0)<<box(_sav_szelesseg-2,_sav_magassag-2);
							_mindhamis=false;

						}
						if(i==_eger_melyik_elemen ) {
							kijelzettek<<move_to(0+1,0+(i-_mi_az_elso)*_sav_magassag+1)<<color(0,122,223)<<box(_sav_szelesseg-2,_sav_magassag-2);
							_mindhamis=false;

						}

					}
					if(_eger_melyik_elemen==-1 && _nyilak_melyik_elemen==i) {
						kijelzettek<<move_to(0+1,0+(i-_mi_az_elso)*_sav_magassag+1)<<color(0,122,223)<<box(_sav_szelesseg-2,_sav_magassag-2);
						_mindhamis=false;

					}
					if(_eger_melyik_elemen==i && _nyilak_melyik_elemen!=i) {
						gout<<move_to(0+1,0+(i-_mi_az_elso)*_sav_magassag+1)<<color(0,122,223)<<box(_sav_szelesseg-2,_sav_magassag-2);
						_mindhamis=false;

					}
					if(_mindhamis)
						kijelzettek<<move_to(0+1,0+(i-_mi_az_elso)*_sav_magassag+1)<<color(0,0,0)<<box(_sav_szelesseg-2,_sav_magassag-2);


				}


				kijelzettek<<move_to(0+_sav_szelesseg/2-gout.twidth(_mezok[i])/2,0+((i-_mi_az_elso)*_sav_magassag)+10+(gout.cascent()+gout.cdescent())/2)<<color(255,243,233)<<text(_mezok[i]);
			}


			gout<<stamp(kijelzettek,_x,_y+_size_y);


		}
	} else  {
		if(_mennyi_fer_ki<_mezok.size())
			gout<<move_to(_x,_y+_size_y)<<color(0,0,0)<<box(_sav_szelesseg+1,_sav_magassag*_mennyi_fer_ki+2);
		else
			gout<<move_to(_x,_y+_size_y)<<color(0,0,0)<<box(_sav_szelesseg+1,_sav_magassag*_mezok.size()+2);
		gout<<move_to(_x+_size_x,_y)<<color(0,0,0)<<box(20,_size_y);
	}




	gout<<stamp(nyil,_x+_size_x-15,_y+_size_y-20);


}
void ChoosingWidget::handle(event ev)
{
	if (ev.type == ev_mouse && is_selected(ev.pos_x, ev.pos_y) && ev.button==btn_left)
		{
		    _focused=true;
            if(!_nyiljon_e_le)
                _gordul_e=true;
		}
	if ( ev.type == ev_mouse && is_lenyilo_gomb(ev) && _focused) {
		_gordul_e=true;
	}


	if(!_gordul_e) {
		if (ev.type == ev_mouse && !is_selected(ev.pos_x, ev.pos_y) && ev.button==btn_left) {
			_eger_melyik_elemen=-1;
			_focused=false;
		}

	}
	if(_focused) {
		if(ev.type==ev_mouse && ev.button==btn_wheeldown && !_kifer_e_minden_mezo) {
			if(_nyiljon_e_le)
                _gordul_e=true;
			if(_nyilak_melyik_elemen<_mezok.size()-1) {

				if(_mi_az_elso<_mezok.size()-_mennyi_fer_ki) {
					_mi_az_elso++;
					_eger_melyik_elemen++;
				}
			}

		}
		if(ev.type==ev_key && ev.keycode==key_down && _eger_melyik_elemen==-1) {
			if(_nyiljon_e_le)
                _gordul_e=true;
			if(_nyilak_melyik_elemen<_mezok.size()-1) {
				_nyilak_melyik_elemen++;

				if(!_kifer_e_minden_mezo && _mi_az_elso<_mezok.size()-_mennyi_fer_ki) {
					_mi_az_elso++;

				}
			}

			if(_nyilak_melyik_elemen==-1)
				_nyilak_melyik_elemen=0;
		}
		if(ev.type==ev_key && ev.keycode==key_up && _eger_melyik_elemen==-1 ) {
			if(_nyiljon_e_le)
                _gordul_e=true;
			if(_nyilak_melyik_elemen>0) {

				_nyilak_melyik_elemen--;

				if(!_kifer_e_minden_mezo && _mi_az_elso>0)
					_mi_az_elso--;


			}
		}

		if(ev.type==ev_mouse && ev.button==btn_wheelup &&!_kifer_e_minden_mezo) {
			if(_nyiljon_e_le)
                _gordul_e=true;
			if(_nyilak_melyik_elemen>-1) {
				if(_mi_az_elso>0) {
					_eger_melyik_elemen--;
					_mi_az_elso--;
				}
			}
		}
	}


	if (_gordul_e ) {
		if(ev.button==-btn_left && ev.pos_x>=_x+_size_x && ev.pos_x<=_x+_size_x+20 && ev.pos_y>=_y && ev.pos_y<=_y+_size_y/2) {
			_mi_az_elso=0;
			_nyilak_melyik_elemen=0;
		}
		if(ev.button==-btn_left && ev.pos_x>=_x+_size_x && ev.pos_x<=_x+_size_x+20 && ev.pos_y>=_y+_size_y/2 && ev.pos_y<=_y+_size_y) {
			_mi_az_elso=_mezok.size()-_mennyi_fer_ki;
			_nyilak_melyik_elemen=_mezok.size()-_mennyi_fer_ki-2;
		}

		if(ev.type==ev_key && ev.keycode==key_enter&& _nyilak_melyik_elemen!=-1) {
			_valasztott=_nyilak_melyik_elemen;
			_nyilak_melyik_elemen=-1;
			_eger_melyik_elemen=-1;
			if(_nyiljon_e_le)
                _gordul_e=false;
            _focused=false;//klédaskdddddddddddddddddddddd
			_mi_az_elso=0;
		}

		if (ev.type == ev_mouse && !is_selected(ev.pos_x, ev.pos_y) ) {

			if(ev.type == ev_mouse  && !is_selected_lenyilo_menu(ev)&& _kifer_e_minden_mezo) {
				_eger_melyik_elemen=-1;
				_nyilak_melyik_elemen=-1;
				if(_nyiljon_e_le)
                    _gordul_e=false;
				_mi_az_elso=0;
			}



			if(!_kifer_e_minden_mezo && !(ev.pos_x>=_x+_size_x && ev.pos_x<=_x+_size_x+20 && ev.pos_y>=_y && ev.pos_y<=_y+_size_y))
				if(ev.type == ev_mouse  && !is_selected_lenyilo_menu(ev)) {
					_eger_melyik_elemen=-1;
					_nyilak_melyik_elemen=-1;
					if(_nyiljon_e_le)
                        _gordul_e=false;
					_mi_az_elso=0;
				}

		}
		for (unsigned int i=0; i<_mezok.size(); i++) {

			if(ev.type == ev_mouse  && ev.pos_x>_x &&ev.pos_x<_x+_sav_szelesseg &&
					ev.pos_y>_y+_size_y+(i-_mi_az_elso)*_sav_magassag && ev.pos_y<_y+_size_y+(i-_mi_az_elso)*_sav_magassag+_sav_magassag) {
				_eger_melyik_elemen=i;
				_nyilak_melyik_elemen=i;
			}
			if(_kifer_e_minden_mezo) {
				if (ev.type == ev_mouse && ev.button==-btn_left && ev.pos_x>_x &&ev.pos_x<_x+_sav_szelesseg
						&& ev.pos_y>_y+_size_y+(i-_mi_az_elso)*_sav_magassag &&
						ev.pos_y<_y+_size_y+(i-_mi_az_elso)*_sav_magassag+_sav_magassag) {
					_valasztott=i;
					if(_nyiljon_e_le)
                        _gordul_e=false;
                    _focused=false;//klédaskdddddddddddddddddddddd
					_eger_melyik_elemen=-1;
					_nyilak_melyik_elemen=-1;
					_mi_az_elso=0;
					break;
				}
			} else {
				if (ev.type == ev_mouse && ev.button==-btn_left && ev.pos_x>_x &&ev.pos_x<_x+_sav_szelesseg
						&& ev.pos_y>_y+_size_y+(i)*_sav_magassag &&
						ev.pos_y<_y+_size_y+(i)*_sav_magassag+_sav_magassag) {
					_valasztott=(i+_mi_az_elso);
					if(_nyiljon_e_le)
                        _gordul_e=false;
                    _focused=false;//klédaskdddddddddddddddddddddd
					_eger_melyik_elemen=-1;
					_nyilak_melyik_elemen=-1;
					_mi_az_elso=0;
					break;
				}
			}
		}


	}

	if(_y+_size_y+_mezok.size()*_sav_magassag>=700-_sav_magassag)
		_kifer_e_minden_mezo=false;
	if(!_focused) {
        if(_nyiljon_e_le)
            _gordul_e=false;
		_eger_melyik_elemen=-1;
		_nyilak_melyik_elemen=-1;
		_mi_az_elso=0;
	}
}
string ChoosingWidget::getextrainfo()
{
	string valasz="A _mezok vektor elemei:";
	for (unsigned int i=0; i<_mezok.size(); i++) {
		stringstream ss;
		ss<<i+1;
		string szam;
		ss>>szam;
		ss.clear();
		valasz+=szam;
		valasz+=". elem:";
		valasz+=_mezok[i];
		if(i<_mezok.size()-1)
			valasz+=", ";

	}
	valasz+=". A kiválasztott elem jelenleg a(z): ";
	valasz+=_mezok[_valasztott];
	return valasz;
}
bool ChoosingWidget::is_focused()
{
	return _focused;
}
bool ChoosingWidget::is_gordul()
{
	return _gordul_e;
}
bool ChoosingWidget::is_lenyilos_widget()
{
	return true;
}
void ChoosingWidget::setfocused()
{
	_focused=!_focused;
}
void ChoosingWidget::HozzafuzMezok(string text)
{
    _mezok.push_back(text);
}

