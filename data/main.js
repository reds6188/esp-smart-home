const HOST_NAME = `http://127.0.0.1:3000`;
//const HOST_NAME = ``;
const VERSION = '/version';

function httpGet(url = "") {
	return fetch(HOST_NAME + url, {
		method: 'GET',
	}).then(response => {
		if(!response.ok) {
			throw new Error(`Request error: ${response.status}`);
		}
		return response.json();
	}).catch(error => {
		console.error('Error: ', error);
	});
}

function getVersion() {
	httpGet(VERSION).then(data => {
		console.log('Received data', data);
		document.getElementById('version').innerText = `Version: ${data.version}`;
	});
}

window.addEventListener('load', getVersion);