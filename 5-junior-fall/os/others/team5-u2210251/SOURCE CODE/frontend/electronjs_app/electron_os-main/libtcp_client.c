// tcp_client.c
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <json-c/json.h>

//-----------------------------DOCTOR--------------------------------
// overall function for creating sockets
int creatSocket() { 
    int sock = 0; 
    struct sockaddr_in server; 
    sock = socket(AF_INET ,SOCK_STREAM , 0 ) ; 
    if(sock == -1 ) { 
        perror("Socket creation failed"); 
        return -1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(9999);

    if (inet_pton(AF_INET, "192.168.196.22", &server.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(sock);
        return -1;
    }

    
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Connection failed");
        close(sock);
        return -1;
    }
    return sock;
}

//overall receive function
char *sendAndReceiveMessage(int sock , const char *message) {
    int read_size;
    char *server_message = malloc(4096);
    if (!server_message) {
        perror("Memory allocation failed");
        close(sock);
        return NULL;
    }

    if (send(sock, message, strlen(message), 0) == -1) {
        perror("Send failed"); 
        close(sock);
        return NULL;
    }

    read_size = read(sock, server_message, 4096);
    if (read_size <= 0) {
        perror("Reading error");
        free(server_message);
        close(sock);
        return NULL;
    }

    server_message[read_size] = '\0';
    return server_message;
}   

//ready
char *getRegions( ) { 

    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("getRegions"));
    
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response;   
}

//ready
char *docLogin (char *id, char *password) { 
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("docLogin"));

    struct json_object *subobject = json_object_new_array() ; 
    json_object_array_add(subobject, json_object_new_string(id)); 
    json_object_array_add(subobject, json_object_new_string(password));

    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response;   
}

char *getDocs (int hospitalID, char *spec) { 
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("getDocs"));

    struct json_object *subobject = json_object_new_array() ; 
    json_object_array_add(subobject, json_object_new_int(hospitalID)); 
    json_object_array_add(subobject, json_object_new_string(spec));

    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response;   
}

//ready
char *docReg(char *FullName, char *Spec,char *Role,int HospitalID,char *PhoneNumber,char *Email ,char *Password){ 
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("docReg"));

    struct json_object *subobject = json_object_new_array() ; 
    json_object_array_add(subobject, json_object_new_string(FullName)); 
    json_object_array_add(subobject, json_object_new_string(Spec));
    json_object_array_add(subobject, json_object_new_string(Role));
    json_object_array_add(subobject, json_object_new_int(HospitalID));
    json_object_array_add(subobject, json_object_new_string(PhoneNumber));
    json_object_array_add(subobject, json_object_new_string(Email));
    json_object_array_add(subobject, json_object_new_string(Password));

    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response;   
}

//ready
char *getCaseHistory(char *patientID){
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("getCaseHistory"));

    struct json_object *subobject = json_object_new_array() ; 
    json_object_array_add(subobject, json_object_new_string(patientID)); 

    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response;   
}

//ready
char* getDistricts(char *regionName) {
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("getDistricts"));

    struct json_object *subobject = json_object_new_array() ; 
    json_object_array_add(subobject,json_object_new_string(regionName)); 

    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response;   
}

//ready
char *getHospitals(char *region,char *district){
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("getHospitals"));

    struct json_object *subobject = json_object_new_array() ;  
    json_object_array_add(subobject, json_object_new_string(region)); 
    json_object_array_add(subobject, json_object_new_string(district)); 

    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response;   
}

//ready
char *getDocNotification(char *Id, char *lastLogin){ 
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("getDocNotification"));

    struct json_object *subobject = json_object_new_array() ;  
    json_object_array_add(subobject, json_object_new_string(Id)); 
    json_object_array_add(subobject, json_object_new_string(lastLogin)); 

    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response;   
}

//ready
char *judgeNotification(char* id, char *status, char *tableName) { 
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("judgeNotification"));

    struct json_object *subobject = json_object_new_array() ;  
    json_object_array_add(subobject, json_object_new_string(id)); 
    json_object_array_add(subobject, json_object_new_string(status)); 
    json_object_array_add(subobject, json_object_new_string(tableName)); 

    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response;   
}

//ready
char *getSchedule(char *date,char *doctorID) { 
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("getSchedule"));

    struct json_object *subobject = json_object_new_array() ;  
    json_object_array_add(subobject, json_object_new_string(doctorID)); 
    json_object_array_add(subobject, json_object_new_string(date)); 

    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response;   
}

//ready
char *getHourInfo(char *doctorID,char *DateTime) { 
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("getHourInfo"));

    struct json_object *subobject = json_object_new_array() ;  
    json_object_array_add(subobject, json_object_new_string(doctorID)); 
    json_object_array_add(subobject, json_object_new_string(DateTime)); 

    //merge objectss
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response;   
}

//ready
char *selectHospital(char *name, char* region, char *district) { 
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("selectHospital"));

    struct json_object *subobject = json_object_new_array() ;  
    json_object_array_add(subobject, json_object_new_string(name)); 
    json_object_array_add(subobject, json_object_new_string(region)); 
    json_object_array_add(subobject, json_object_new_string(district)); 
    //json_object_array_add(subobject, json_object_new_string(address)); 

    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response;   
}

//ready
char *modifyApp (int appointmentID,char *status) { 
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("modifyApp"));

    struct json_object *subobject = json_object_new_array() ;  
    json_object_array_add(subobject, json_object_new_int(appointmentID)); 
    json_object_array_add(subobject, json_object_new_string(status)); 

    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response;   
}


//----------------------------------------PATIENT-----------------------------

//ready
char *regPatient(char*name,char *DOB,char*Address , char*PhoneNumber, char*Email, char *PassportID, char*Citizenship, char*Password) { 
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("regPatient"));

    struct json_object *subobject = json_object_new_array() ;  
    json_object_array_add(subobject, json_object_new_string(name)); 
    json_object_array_add(subobject, json_object_new_string(DOB)); 
    json_object_array_add(subobject, json_object_new_string(Address)); 
    json_object_array_add(subobject, json_object_new_string(PhoneNumber)); 
    json_object_array_add(subobject, json_object_new_string(Email)); 
    json_object_array_add(subobject, json_object_new_string(PassportID)); 
    json_object_array_add(subobject, json_object_new_string(Citizenship)); 
    json_object_array_add(subobject, json_object_new_string(Password)); 

    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response;   
}

//ready
char *patientLogin(char *id, char *Password){
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("patientLogin"));

    struct json_object *subobject = json_object_new_array() ;  
    json_object_array_add(subobject, json_object_new_string(id)); 
    json_object_array_add(subobject, json_object_new_string(Password)); 

    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response;   
}

//ready
char *getSpecs(char *HospitalID) { 
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("getSpecs"));

    struct json_object *subobject = json_object_new_array() ;   
    json_object_array_add(subobject, json_object_new_string(HospitalID)); 

    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response;   
}

//ready
char *selectDoc (int HospitalID, char *FullName) { 
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("selectDoc"));

    struct json_object *subobject = json_object_new_array() ;   
    json_object_array_add(subobject, json_object_new_int(HospitalID)); 
    json_object_array_add(subobject, json_object_new_string(FullName)); 

    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response;   
}

//ready 
char *joinWaitlist(char *PatientID, char *doctorId, char *Date) { 
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("joinWaitlist"));

    struct json_object *subobject = json_object_new_array() ;   
    json_object_array_add(subobject, json_object_new_string(PatientID)); 
    json_object_array_add(subobject, json_object_new_string(doctorId));
    json_object_array_add(subobject, json_object_new_string(Date)); 

    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response; 
}

//ready 
char *getWaitlist(char *DateTime , char *DoctorID ) { 
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("getWaitlist"));

    struct json_object *subobject = json_object_new_array() ;   
    json_object_array_add(subobject, json_object_new_string(DateTime)); 
    json_object_array_add(subobject, json_object_new_string(DoctorID)); 

    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response;  
}

//ready 
char *getNotif(char *PatientID , char* LastLoginDate){ 
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("getNotif"));

    struct json_object *subobject = json_object_new_array() ;   
    json_object_array_add(subobject, json_object_new_string(PatientID)); 
    json_object_array_add(subobject, json_object_new_string(LastLoginDate)); 

    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response;  
}

//ready
char *modifWaitlist(char*patientId, char* waitlistID, char*Status) { 
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("modifWaitlist"));

    struct json_object *subobject = json_object_new_array() ;   
    json_object_array_add(subobject, json_object_new_string(patientId)); 
    json_object_array_add(subobject, json_object_new_string(waitlistID)); 
    json_object_array_add(subobject, json_object_new_string(Status));

    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response;  
}

//ready
char*myApp( char *patientID) { 
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("myApp"));

    struct json_object *subobject = json_object_new_array() ;   
    json_object_array_add(subobject, json_object_new_string(patientID)); 

    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj   
    close(sock);
    return response; 
}

//ready 
char* modifAppoint(char *patientID, char *AppointmentID, char* status) { 
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("modifAppoint"));

    struct json_object *subobject = json_object_new_array() ;   
    json_object_array_add(subobject, json_object_new_string(patientID)); 
    json_object_array_add(subobject, json_object_new_string(AppointmentID)); 
    json_object_array_add(subobject, json_object_new_string(status)); 
    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response; 
}

// ---------------------------------ADMIN-------------------------------------

//ready
char *adminLogin(char *id,char *Password){ 
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("adminLogin"));

    struct json_object *subobject = json_object_new_array() ;   
    json_object_array_add(subobject, json_object_new_string(id)); 
    json_object_array_add(subobject, json_object_new_string(Password)); 
    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response; 
}

//ready 
char *sqlExe(char *sqlQuery){
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("sqlExe"));

    struct json_object *subobject = json_object_new_array() ;   
    json_object_array_add(subobject, json_object_new_string(sqlQuery));  
    //merge objects
    json_object_object_add(obj, "args", subobject); 
  
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response; 
}

//ready
char *getIP(){ 
    int read_size;
    int sock = creatSocket(); 

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "function", json_object_new_string("getIP"));
    //convert cJSON to JSON string 
    const char *message=json_object_to_json_string(obj); 
    char *response = sendAndReceiveMessage(sock, message);
    json_object_put(obj); // free obj
    close(sock);
    return response;  
}




