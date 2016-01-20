#ifndef IUILISTENER_H
#define IUILISTENER_H

class IUiListener
{
 public:
  enum UiEvent { ONCONNECT,	     \
		 ONRETCONNECT,	     \
		 ONRECEIVEROOM,	     \
		 ONRECEIVEWRONGROOM, \
		 ONREFRESHROOM,	     \
		 ONJOINROOM,	     \
		 ONLEAVEROOM,	     \
		 ONRETJOINROOM,	     \
		 ONCREATEROOM,	     \
		 ONRETCREATEROOMERROR, \
		 STARTGAME,	     \
		 PLAYERJOIN,	     \
		 PLAYERQUIT,	     \
		 ONREADY,	     \
		 DISCONNECT,	     \
		 ONCREATEENTITY,     \
		 ONPOSITIONUPDATE,   \
		 ONUPDATEENTITY,     \
		 ONDESTROYENTITY,    \
		 ONUPDATELIFE,	     \
		 ONSENDCREATEENTITY, \
		 ONSCORE,	     \
		 ONSENDROOMBACK,     \
		 ONFINALSCORE,	     \
		 ONSHOT
  };
  virtual ~IUiListener(){}
  virtual void OnEvent(UiEvent event, void*) = 0;
 protected:
 private:
};

#endif // ISCENE_H   
