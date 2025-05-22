//const HOST_NAME = `http://127.0.0.1:3000`;
const HOST_NAME = ``;
const VERSION = '/version';
const CONNECTION = '/connection';

// HTTP GET request -------------------------------------------------
async function httpGet(url = "") {
	try {
		const response = await fetch(HOST_NAME + url, {
			method: 'GET',
		});
		if (!response.ok) {
			throw new Error(`GET Request error: ${response.status}`);
		}
		return await response.json();
	} catch (error) {
		throw new Error(error)
	}
}

// HTTP POST request ------------------------------------------------
async function httpPost(url = "", data = {}) {
	try {
		const response = await fetch(HOST_NAME + url, {
			method: 'POST',
			headers: {
				'Content-Type': 'application/json',
			},
			body: JSON.stringify(data)
		});
		if (!response.ok) {
			throw new Error(`POST Request error: ${response.status}`);
		}
		return await response.json();
	} catch (error) {
		throw new Error(error)
	}
}

function getVersion() {
	httpGet(VERSION).then(data => {
		console.log('Received data', data);
		if(data !== undefined) {
			document.getElementById('version').innerText = data.version ?? '-';
			document.getElementById('date').innerText = data.date ?? '-';
		}
	}).catch(err => {
		console.error(err);
	});
}

function getWifiInfo() {
	httpGet(CONNECTION).then(data => {
		console.log('Received data', data);
		if(data !== undefined) {
			document.getElementById('current-ssid').innerText = data.ssid ?? '-';
			document.getElementById('rssi').innerText = data.rssi ?? '-';
			document.getElementById('mac').innerText = data.mac ?? '-';
		}
	}).catch(err => {
		console.error(err);
	});
}

// Show element [elementClass] belong to group [groupClass] ----------------------
function showElement(elementClass, groupClass) {
    const group_list = document.querySelectorAll(`.${groupClass}`);
    for(let item of group_list) {
        item.classList.replace('flex','hidden');
    }
    document.querySelector(`.${elementClass}.${groupClass}`).classList.replace('hidden','flex');
}

function showPassword() {
	//console.log('Show/hide password')
	let el = document.getElementById('set-password');
	let svg = document.getElementById('view-password').firstElementChild
	let icon = el.type === 'password' ? '#icon-eye' : '#icon-eye-off';
	el.type = el.type === 'password' ? 'text' : 'password'
	svg.href.baseVal = icon;  
}

function sendCredentials() {
	const ssid = document.getElementById('set-ssid').value;
	const password = document.getElementById('set-password').value;
	httpPost(CONNECTION, { ssid, password }).then(data => {
		if(data !== undefined) {
			console.log(data);
		}
	}).catch(err => {
		console.error(err);
	});
}

window.addEventListener('load', getVersion);

const tile_list = document.querySelectorAll('.tile');
for(const tile of tile_list) {
	tile.addEventListener('click', () => { showElement(tile.classList[0], 'section'); });
}

const back_list = document.querySelectorAll('.back');
for(const back of back_list) {
	back.addEventListener('click', () => { showElement('main', 'section'); });
}

//document.getElementsByClassName('wifi tile')[0].addEventListener('click', () => { getWifiInfo() });
document.getElementsByClassName('wifi tile')[0].addEventListener('click', getWifiInfo);
document.getElementById('view-password').addEventListener('click', showPassword);
document.getElementById('save').addEventListener('click', sendCredentials);
document.getElementById('edit').addEventListener('click', () => { showElement('edit-wifi', 'section'); });