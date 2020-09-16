/* globals process global */

const electron = require('electron');
const {app, ipcMain, BrowserWindow} = electron;

//app.commandLine.appendSwitch('enable-features', 'experimental-wasm-simd');
app.commandLine.appendSwitch('experimental-wasm-simd');

// Keep a global reference of the window object, if you don't, the window will
// be closed automatically when the JavaScript object is garbage collected.
let win;

function createWindow () {
   win = {};

   // Create the browser window.
   //const {width, height} = electron.screen.getPrimaryDisplay().workAreaSize;
   //win = new BrowserWindow({width: width, height: height});
   ///*
   win = new BrowserWindow({
      webPreferences: {
         nodeIntegration: true,
         //sandbox: false,
         //allowRunningInsecureContent: true,
         //webSecurity: false,
         //contextIsolation: false
      }
  });
  //*/
   //win = new BrowserWindow();
   win.maximize();

   // and load the index.html of the app.
   win.loadURL(`file://${__dirname}/parser.html`);
   //win.loadURL(`file://${__dirname}/../blis-0.6.1/test.html`);

   // Open the DevTools.
   win.webContents.openDevTools();

   // Emitted when the window is closed.
   win.on('closed', () => {
       // Dereference the window object, usually you would store windows
      // in an array if your app supports multi windows, this is the time
      // when you should delete the corresponding element.
      win = null;
   });
}

// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// Some APIs can only be used after this event occurs.
app.on('ready', createWindow);

// Quit when all windows are closed.
app.on('window-all-closed', () => {
   // On macOS it is common for applications and their menu bar
   // to stay active until the user quits explicitly with Cmd + Q
   if(process.platform !== 'darwin') {
      app.quit();
   }
});

app.on('activate', () => {
   // On macOS it's common to re-create a window in the app when the
   // dock icon is clicked and there are no other windows open.
   if (win === null) {
      createWindow();
   }
});

// In this file you can include the rest of your app's specific main process
// code. You can also put them in separate files and require them here.
