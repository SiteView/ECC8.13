package de.ajaxgui.test;

import de.ajaxgui.Button;
import de.ajaxgui.Label;
import de.ajaxgui.MainForm;
import de.ajaxgui.TextField;

public class TextFieldMainForm extends MainForm {

	private TextField tf1 = null;

	private TextField tf2 = null;

	private Label l3 = null;

	public TextFieldMainForm() {
		Label l1 = new Label("First name:");
		l1.setTop(20);
		l1.setLeft(20);
		this.add(l1);

		tf1 = new TextField();
		tf1.setTop(20);
		tf1.setLeft(80);
		this.add(tf1);

		Label l2 = new Label("Surname:");
		l2.setTop(50);
		l2.setLeft(20);
		this.add(l2);

		tf2 = new TextField();
		tf2.setTop(50);
		tf2.setLeft(80);
		this.add(tf2);

		Button btn = new Button("Send");
		btn.setTop(80);
		btn.setLeft(80);
		btn.addClick(this, "btnClicked");
		this.add(btn);

		l3 = new Label("");
		l3.setTop(120);
		l3.setLeft(90);
		this.add(l3);
	}

	public void btnClicked() {
		l3.setText("Hello " + tf1.getText() + " " + tf2.getText() + "!");
	}
}
