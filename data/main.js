const HOST_NAME = `http://127.0.0.1:3000`;
//const HOST_NAME = ``;
const VERSION = '/version';

async function httpGet(url = "") {
	try {
		const response = await fetch(HOST_NAME + url, {
			method: 'GET',
		});
		if (!response.ok) {
			throw new Error(`Request error: ${response.status}`);
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

// Show element [elementClass] belong to group [groupClass] ----------------------
function showElement(elementClass, groupClass) {
    const group_list = document.querySelectorAll(`.${groupClass}`);
    for(let item of group_list) {
        item.classList.replace('flex','hidden');
    }
    document.querySelector(`.${elementClass}.${groupClass}`).classList.replace('hidden','flex');
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