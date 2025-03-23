// 23.11.26 peti_fetch_fv

// peti_fetch_html(cim2f, helye)
async function peti_fetch_html(cim2f, helye)
	{
		let str = await fetch(cim2f);
		helye.innerHTML = await str.text();
	}
		

// peti_fetch_fv(file, callbackfgv)
async function peti_fetch_fv(file, callbackfgv) {
    let x = await fetch(file);
    let y = await x.text();
    callbackfgv(y);
}
		