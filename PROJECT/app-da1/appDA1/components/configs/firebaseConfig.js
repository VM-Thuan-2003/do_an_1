// Import the functions you need from the SDKs you need
import firebase from 'firebase/compat/app'
import {getDatabase} from 'firebase/database'
const firebaseConfig = {
    apiKey: "AIzaSyD6zga0Ah4-wB3zpNJAjPXI88uMT77R3vg",
    authDomain: "da-1-15997.firebaseapp.com",
    databaseURL: "https://da-1-15997-default-rtdb.europe-west1.firebasedatabase.app",
    projectId: "da-1-15997",
    storageBucket: "da-1-15997.appspot.com",
    messagingSenderId: "1085599421046",
    appId: "1:1085599421046:web:ebb587b31a105e95d1c557",
    measurementId: "G-JHZCVEX661"
};
if(firebase.apps.length === 0){
    firebase.initializeApp(firebaseConfig)
}
const db = getDatabase()
export {db}