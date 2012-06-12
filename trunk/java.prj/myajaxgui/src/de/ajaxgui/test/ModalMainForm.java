package de.ajaxgui.test;

import de.ajaxgui.Button;
import de.ajaxgui.MainForm;

public class ModalMainForm extends MainForm {

	public ModalMainForm() {
		Button btn1 = new Button("Open window");
		btn1.setTop(20);
		btn1.setLeft(20);
		btn1.addClick(this, "btn1Clicked");
		this.add(btn1);
	}

	public void btn1Clicked() {
		ModalForm mf = new ModalForm();
		mf.setLocation(60, 60);
		mf.setDimension(320, 240);
		this.add(mf);
		mf.showDialog();
	}
}
