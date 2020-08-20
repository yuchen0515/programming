#include <stdio.h>
#include <stdint.h>
#include "cJSON.h"


//示範函式
char *create_project_with_deadline(){

    const uint32_t deadline_and_presentation_time[3][2] = {
        {628, 2359},
        {629, 1615},
        {629, 1630}
    };

	//最終回傳的指標位置
    char *string = NULL;
    size_t index = 0;
    cJSON *project_time = NULL;


	//創建一個object，用一個cJSON結構的指標去接他
    cJSON *project= cJSON_CreateObject();

	//加入名字的資訊在object內
	//如果失敗就回傳(加上刪除)
    if (cJSON_AddStringToObject(project , "name", "Yu-Chen Lin") == NULL)
        goto end;

	//第2層資訊，整體為project的時間和截止日期，簡單來說就是第2層元素
    project_time = cJSON_AddArrayToObject(project , "project_time");
    if (project_time == NULL)
        goto end;

    for (index = 0; index < (sizeof(deadline_and_presentation_time) / (2 * sizeof(int32_t))); index++){
        cJSON *project_time_ = cJSON_CreateObject();

        if (cJSON_AddNumberToObject(project_time_, "date", deadline_and_presentation_time[index][0]) == NULL)
            goto end;

        if (cJSON_AddNumberToObject(project_time_, "time", deadline_and_presentation_time[index][1]) == NULL)
            goto end;

        cJSON_AddItemToArray(project_time, project_time_);
    }

	//回傳
    string = cJSON_Print(project);
    if (string == NULL)
        fprintf(stderr, "Failed to print monitor.\n");

end:
    cJSON_Delete(project);
    return string;
}

/* return 1 if the project supports presentation time at 16:15, 0 otherwise */
int32_t supports(const char* const project){

    const cJSON *project_time_= NULL;
    const cJSON *project_time = NULL;
    const cJSON *name = NULL;
    int32_t status = 0;

	//先把傳入的JSON字串剖析程cJSON的結構
    cJSON *project_json = cJSON_Parse(project);

	//當然要檢查有沒有成功，失敗就傳出錯誤訊息
    if (project_json == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL){
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        status = 0;
        goto end;
    }

	//檢查project的名字
    name = cJSON_GetObjectItemCaseSensitive(project_json, "name");
    if (cJSON_IsString(name) && (name->valuestring != NULL)){
        printf("Checking project \"%s\"\n", name->valuestring);
    }

    project_time = cJSON_GetObjectItemCaseSensitive(project_json, "project_time");

	//尋訪陣列中每一個
    cJSON_ArrayForEach(project_time_, project_time){
        cJSON *date = cJSON_GetObjectItemCaseSensitive(project_time_, "date");
        cJSON *time = cJSON_GetObjectItemCaseSensitive(project_time_, "time");

        if (!cJSON_IsNumber(date) || !cJSON_IsNumber(time)){
            status = 0;
            goto end;
        }

        if ((date->valuedouble == 629) && (time->valuedouble == 1615)){
            status = 1;
            goto end;
        }
    }

end:
    cJSON_Delete(project_json);
    return status;
}

int main(){

	char *ptr = create_project_with_deadline();
	printf("%s\n", ptr);

	int32_t status = supports(ptr);
	printf("status: %d\n", status);

	return 0;
}
