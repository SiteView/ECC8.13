package de.ajaxgui.test;

import de.ajaxgui.Label;
import de.ajaxgui.MainForm;
import de.ajaxgui.TabControl;
import de.ajaxgui.TabPage;

public class TabControlMainForm extends MainForm {

	private Label label = null;

	public TabControlMainForm() {
		TabControl tc1 = new TabControl();
		tc1.setTop(20);
		tc1.setLeft(20);
		tc1.setDimension(320, 240);
		this.add(tc1);

		TabPage tp1 = new TabPage("Tab 1");
		tp1.addClick(this, "tp1Clicked");
		tc1.add(tp1);

		TabPage tp2 = new TabPage("Tab 2");
		tp2.addClick(this, "tp2Clicked");
		tc1.add(tp2);

		TabPage tp3 = new TabPage("Tab 3");
		tp3.addClick(this, "tp3Clicked");
		tc1.add(tp3);

		tc1.setSelected(tp2);

		TabControl tc2 = new TabControl();
		tc2.setTop(20);
		tc2.setLeft(20);
		tc2.setDimension(200, 150);
		tp1.add(tc2);

		TabPage tp4 = new TabPage("SubTab 1");
		tp4.addClick(this, "tp4Clicked");
		tc2.add(tp4);

		TabPage tp5 = new TabPage("SubTab 2");
		tp5.addClick(this, "tp5Clicked");
		tc2.add(tp5);

		label = new Label("No news");
		label.setLocation(80, 280);
		this.add(label);
	}

	public void tp1Clicked() {
		label.setText("Tab 1 activated");
	}

	public void tp2Clicked() {
		label.setText("Tab 2 activated");
	}

	public void tp3Clicked() {
		label.setText("Tab 3 activated");
	}

	public void tp4Clicked() {
		label.setText("SubTab 1 activated");
	}

	public void tp5Clicked() {
		label.setText("SubTab 2 activated");
	}
}
