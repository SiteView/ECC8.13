package de.ajaxgui;

import java.util.ArrayList;

public class ListViewItem {
	private ArrayList<String> code = new ArrayList<String>();

	private Object notice = null;

	private ArrayList<String> texte = new ArrayList<String>();

	public void addText(String text) {
		texte.add(text);
		code.add("{text:\"" + text + "\"}");
	}

	protected ArrayList getCode() {
		return code;
	}

	public Object getNotice() {
		return notice;
	}

	public String getText(int index) {
		return texte.get(index);
	}

	public void setNotice(Object notice) {
		this.notice = notice;
	}
}
