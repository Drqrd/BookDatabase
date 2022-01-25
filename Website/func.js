var blankImg = "data:image/gif;base64,R0lGODlhAQABAIAAAP///wAAACH5BAEAAAAALAAAAAABAAEAAAICRAEAOw==";

const btns = ["s_1","s_2","s_3"];


function sortAsc(btnId)
{
		var btn = document.getElementById(btnId);
		var img = btn.childNodes[3];
		img.src = "Sorting-Icon-Up-512px.png";

		const _btns = btns.filter(id => id != btnId);
		_btns.forEach(ele => sortRes(ele));	

		btn.onclick = function () { sortDsc(this.id); };
}

function sortDsc(btnId)
{
	var btn = document.getElementById(btnId);
	var img = btn.childNodes[3];
	img.src = "Sorting-Icon-Down-512px.png";

	btn.onclick = function () { sortRem(this.id); };
}

function sortRem(btnId)
{
	var btn = document.getElementById(btnId);
	var img = btn.childNodes[3];
	img.src = blankImg;

	btn.onclick = function () { sortAsc(this.id); };
}

function sortRes(btnId)
{
	var btn = document.getElementById(btnId);
	var img = btn.childNodes[3];
	img.src = blankImg;

	btn.onclick = function () { sortAsc(this.id); };
}