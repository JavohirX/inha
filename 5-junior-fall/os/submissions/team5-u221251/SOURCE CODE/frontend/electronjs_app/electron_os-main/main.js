const { app, BrowserWindow, ipcMain } = require('electron');
const koffi = require('koffi');
const path = require("path");

const appPath = app.getAppPath();
const libPath = path.join(__dirname, 'libtcp_client.so');
const libtcp_client = koffi.load(libPath);

// Load the functions from the native library
//----------------------------------DOCTOR-----------------------------------------------
const docLogin = libtcp_client.func('char* docLogin(char* id, char* password)');
const getRegions = libtcp_client.func('char* getRegions()');
const docReg = libtcp_client.func('char* docReg(char* FullName, char* Spec, char* Role, int HospitalID, char* PhoneNumber, char* Email, char* Password)');
const getCaseHistory = libtcp_client.func('char* getCaseHistory(char* patientID)');
const getDistricts = libtcp_client.func('char* getDistricts(char* regionName)');
const getHospitals = libtcp_client.func('char* getHospitals(char* region, char* district)');
const getDocNotification = libtcp_client.func('char* getDocNotification(char *Id, char* lastLogin)');
const judgeNotification = libtcp_client.func('char* judgeNotification(char *id, char* status, char* tableName)');
const getSchedule = libtcp_client.func('char* getSchedule(char *date, char *doctorID)');
const getHourInfo = libtcp_client.func('char* getHourInfo(char *doctorID, char *DateTime)');
const selectHospital = libtcp_client.func('char* selectHospital(char *name, char *region, char *district, char *address)');
const modifyApp = libtcp_client.func('char* modifyApp(int appointmentID, char *status)');
// -----------------------------------PATIENT-------------------------------------
const regPatient = libtcp_client.func('char* regPatient(char* name, char* DOB, char* Address, char* PhoneNumber, char* Email, char* PassportID, char* Citizenship, char* Password)');
const patientLogin = libtcp_client.func('char* patientLogin(char* id, char* Password)');
const getSpecs = libtcp_client.func('char* getSpecs(char* HospitalID)');
const selectDoc = libtcp_client.func('char *selectDoc (int HospitalID, char *FullName)');
const joinWaitlist = libtcp_client.func('char *joinWaitlist(char *PatientID, char *doctorId, char *Date)');
const getWaitlist= libtcp_client.func('char *getWaitlist(char *DateTime , char *DoctorID ) ');
const getDocs = libtcp_client.func('char *getDocs (int hospitalID, char *spec)');
const getNotif = libtcp_client.func('char *getNotif(char *PatientID , char* LastLoginDate)');
const modifWaitlist = libtcp_client.func('char *modifWaitlist(char*patientId, char* waitlistID, char*Status) ');
const myApp = libtcp_client.func('char*myApp( char *patientID)');
const modifAppoint = libtcp_client.func('char* modifAppoint(char *patientID, char *AppointmentID, char* status)');
const adminLogin = libtcp_client.func('char *adminLogin(char *id,char *Password)');
const sqlExe = libtcp_client.func('char *sqlExe(char *sqlQuery)');
const getIP = libtcp_client.func('char *getIP()');


let mainWindow;


const createWindow = () => {
    mainWindow = new BrowserWindow({
        webPreferences: {
            webSecurity: false,
            nodeIntegration: true,
            contextIsolation: false
        },
    });
    mainWindow.maximize();

    //mainWindow.loadFile(path.join(__dirname, '..', '/build/index.html')) for build
    mainWindow.loadURL('http://localhost:5173/');
    mainWindow.on('closed', () => {
        mainWindow = null;
    });
};

app.whenReady().then(() => {
    createWindow();
    // ready
    ipcMain.handle('doc-login', async (event, id, password) => {
        try {
            const response = docLogin(id,password);
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in doc-login:', error);
            return { success: false, error: error.message };
        }
    });
    //ready
    ipcMain.handle('get-regions', async () => {
        try {
            const response = getRegions();
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in get-regions:', error);
            return { success: false, error: error.message };
        }
    });

    //ready
    ipcMain.handle('doc-reg', async (event, FullName, Spec, Role, HospitalID, PhoneNumber, Email, Password) => {
        try {
            const response = docReg(FullName,Spec,Role,HospitalID,PhoneNumber,Email,Password);
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in doc-reg:', error);
            return { success: false, error: error.message };
        }
    });
    
    ipcMain.handle('get-docs', async (event, hospitalID, spec) => {
        try {
            const response = getDocs(hospitalID, spec);

            return { success: true, data: response };
        } catch (error) {
            console.error('Error in doc-reg:', error);
            return { success: false, error: error.message };
        }
    });

    //ready
    ipcMain.handle('get-case-history', async (event, patientID) => {
        try {
            const response = getCaseHistory(patientID);
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in get-case-history:', error);
            return { success: false, error: error.message };
        }
    });

    ipcMain.handle('get-districts', async (event, regionName) => {
        try {
            const response = getDistricts(regionName);
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in get-districts:', error);
            return { success: false, error: error.message };
        }
    });

    ipcMain.handle('get-hospitals', async (event, region, district) => {
        try {
            const response = getHospitals(region, district);

            return { success: true, data: response };
        } catch (error) {
            console.error('Error in get-hospitals:', error);
            return { success: false, error: error.message };
        }
    });

    ipcMain.handle('get-doc-notification', async (event, Id, lastLogin) => {
        try {
            const response = getDocNotification(Id, lastLogin);
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in get-doc-notification:', error);
            return { success: false, error: error.message };
        }
    });

    ipcMain.handle('judge-notification', async (event, id, status, tableName) => {
        try {
            const response = judgeNotification(id, status, tableName);
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in judge-notification:', error);
            return { success: false, error: error.message };
        }
    });

    ipcMain.handle('get-schedule', async (event, date, doctorID) => {
        try {
            const response = getSchedule(date, doctorID);
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in get-schedule:', error);
            return { success: false, error: error.message };
        }
    });

    ipcMain.handle('get-hour-info', async (event, doctorID, DateTime) => {
        try {
            const response = getHourInfo(doctorID, DateTime);
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in get-hour-info:', error);
            return { success: false, error: error.message };
        }
    });

    ipcMain.handle('select-hospital', async (event, name, region, district, address) => {
        try {
            const response = selectHospital(name, region, district, address);
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in select-hospital:', error);
            return { success: false, error: error.message };
        }
    });

    ipcMain.handle('modify-app', async (event, appointmentID, status) => {
        try {
            const response = modifyApp(appointmentID, status);

            return { success: true, data: response };
        } catch (error) {
            console.error('Error in modify-app:', error);
            return { success: false, error: error.message };
        }
    });

    ipcMain.handle('reg-patient', async (event, name, DOB, Address, PhoneNumber, Email, PassportID, Citizenship, Password) => {
        try {
            const response =regPatient(name, DOB, Address, PhoneNumber, Email, PassportID, Citizenship, Password);
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in reg-patient:', error);
            return { success: false, error: error.message };
        }
    });

    ipcMain.handle('patient-login', async (event, id, Password) => {
        try {

            const response = patientLogin(id, Password);
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in patient-login:', error);
            return { success: false, error: error.message };
        }
    });

    ipcMain.handle('get-specs', async (event, HospitalID, Spec) => {
        try {
            const response = getSpecs(HospitalID, Spec);
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in get-specs:', error);
            return { success: false, error: error.message };
        }
    });
    ipcMain.handle('selectDoc', async (event, HospitalID, FullName) => {
        try {
            const response = selectDoc(HospitalID, FullName);
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in selectDoc:', error);
            return { success: false, error: error.message };
        }
    });

    ipcMain.handle('joinWaitlist', async (event, DateTime, doctorId, Date) => {
        try {
            const response = joinWaitlist(DateTime, doctorId, Date);
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in joinWaitlist:', error);
            return { success: false, error: error.message };
        }
    });

    ipcMain.handle('getWaitlist', async (event,date, DoctorID) => {
        try {
            const response = getWaitlist(date, DoctorID);
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in getWaitlist:', error);
            return { success: false, error: error.message };
        }
    });

    ipcMain.handle('getNotif', async (event, PatientID, LastLoginDate) => {
        try {
            const response = getNotif(PatientID, LastLoginDate);
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in getNotif:', error);
            return { success: false, error: error.message };
        }
    });

    ipcMain.handle('modifWaitlist', async (event, patientId, waitlistID, Status) => {
        try {
            const response = modifWaitlist(patientId, waitlistID, Status);
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in modifWaitlist:', error);
            return { success: false, error: error.message };
        }
    });

    ipcMain.handle('myApp', async (event, patientID) => {
        try {
            const response = myApp(patientID);
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in myApp:', error);
            return { success: false, error: error.message };
        }
    });

    ipcMain.handle('modifAppoint', async (event, patientID, AppointmentID,status) => {
        try {
            const response = modifAppoint(patientID,AppointmentID,status);
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in modifAppoint:', error);
            return { success: false, error: error.message };
        }
    });

    ipcMain.handle('adminLogin', async (event, id, Password) => {
        try {
            const response = adminLogin(id,Password);
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in adminLogin:', error);
            return { success: false, error: error.message };
        }
    });

    ipcMain.handle('sqlExe', async (event, sqlQuery) => {
        try {
            const response = sqlExe(sqlQuery);
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in sqlExe:', error);
            return { success: false, error: error.message };
        }
    });

    ipcMain.handle('getIP', async (event) => {
        try {
            const response = getIP();
            return { success: true, data: response };
        } catch (error) {
            console.error('Error in getIP:', error);
            return { success: false, error: error.message };
        }
    });

});

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') app.quit();
});
