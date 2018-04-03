/*
  FluoTube.h - FluoTube library
  Copyright (c) 2017 Adriano Costanzo.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/

/*	NOMENCLATURA 
			FluoTube.WiFi.begin();
			FluoTube.WiFi.connect();

			FluoTube.Cloud.Google.email.send();
			FluoTube.Cloud.Telegram.connect();
			FluoTube.Cloud.ThingSpeak.connect();

			FluoTube.REST.connect();
			FluoTube.REST.send();

			FluoTube.MQTT.connect();
			FluoTube.MQTT.broker();				
*/

#ifndef FLUOTUBE_H_
#define FLUOTUBE_H_

#include "FluoTube_WIFI.h"

// FluoTube Class
class FluoTubeClass
{

	public:
		FluoTubeClass(); //constructor

		FluoTubeClass_WIFI 	  WiFi;

		void Begin();
        void Run();
        void sendMsgToESP(String data);

	private:

	protected:
				
};

extern FluoTubeClass FluoTube;

#endif /* FLUOTUBE_H_ */
