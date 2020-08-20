#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <curl/curl.h>

int main(int32_t argc, char *argv[]){

	int32_t record = 0;
	char *tempp;
	sscanf(argv[1], "%d", &record);

	CURL *curl;
	CURLcode res;
	FILE *pfile = NULL;

	curl = curl_easy_init();
	char *str = calloc(2048, sizeof(char));

	if (curl) {
		struct curl_slist *chunk = NULL;

		chunk = curl_slist_append(chunk, "Accept: application/json");
		char strr[40496] = "Authorization: hmac username=\"80544ea7295746b6af9e2c6692c416f5\", algorithm=\"hmac-sha1\", headers=\"x-date\"";

		pfile = popen("export LC_TIME=en_US.utf8 && now=$(env TZ=GMT date \'+%a, %d %b %Y %T %Z\') && signature=$(printf \"x-date: $now\" | openssl sha1 -binary -hmac \"W6GRZiayBhUTF47r8PeZc6YCk1g\" | base64) &&  echo \"$signature\" && echo \"$now\"", "r");
		tempp = fgets(str, 2047, pfile);
		str[strlen(str)-1] = '\0';
		strcat(strr, ", signature=\"");
		strcat(strr, str);
		strcat(strr, "\"");
		chunk = curl_slist_append(chunk, strr);

		char stp[40496];
		tempp = fgets(str, 2047, pfile);
		str[strlen(str)-1] = '\0';
		strcat(stp, "x-date: ");
		strcat(stp, str);

		chunk = curl_slist_append(chunk, stp);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

		if (record == 1)
		//sort by ScheduleArrivalTime
			curl_easy_setopt(curl, CURLOPT_URL, "https://ptx.transportdata.tw/MOTC/v2/Air/FIDS/Airport/Arrival?$orderby=ScheduleArrivalTime&$format=JSON");
		else if (record == 2)
		//sort by FlightNumber.
			curl_easy_setopt(curl, CURLOPT_URL, "https://ptx.transportdata.tw/MOTC/v2/Air/FIDS/Airport/Arrival?$orderby=FlightNumber&$format=JSON");
		else if (record == 3)
		//sort by AirlineID
			curl_easy_setopt(curl, CURLOPT_URL, "https://ptx.transportdata.tw/MOTC/v2/Air/FIDS/Airport/Arrival?$orderby=AirlineID&$format=JSON");
		curl_easy_perform(curl);
		/* always cleanup */ curl_easy_cleanup(curl); 
		/* free the custom headers */ 
		curl_slist_free_all(chunk);
	}
	pclose(pfile);

	return 0;
}
