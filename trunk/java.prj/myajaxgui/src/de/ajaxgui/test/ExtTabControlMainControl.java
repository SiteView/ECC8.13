package de.ajaxgui.test;

import de.ajaxgui.ExtTabControl;
import de.ajaxgui.ExtTabPage;
import de.ajaxgui.Label;
import de.ajaxgui.MainForm;

public class ExtTabControlMainControl extends MainForm {

	private Label label = null;

	public ExtTabControlMainControl() {
		ExtTabControl etc1 = new ExtTabControl();
		etc1.setTop(20);
		etc1.setLeft(20);
		etc1.setDimension(450, 320);
		this.add(etc1);

		ExtTabPage etp1 = new ExtTabPage("ExtTab 1");
		etp1.setIcon("themes/icons/kids/32/alarm.png");
		etp1.addClick(this, "etp1Clicked");
		etc1.add(etp1);

		ExtTabPage etp2 = new ExtTabPage("ExtTab 2");
		etp2.setIcon("themes/icons/kids/32/babelfish.png");
		etp2.addClick(this, "etp2Clicked");
		etc1.add(etp2);

		ExtTabPage etp3 = new ExtTabPage("ExtTab 3");
		etp3.setIcon("themes/icons/kids/32/mac.png");
		etp3.addClick(this, "etp3Clicked");
		etc1.add(etp3);

		etc1.setSelected(etp2);

		ExtTabControl etc2 = new ExtTabControl();
		etc2.setTop(20);
		etc2.setLeft(20);
		etc2.setDimension(250, 200);
		etp1.add(etc2);

		ExtTabPage etp4 = new ExtTabPage("ExtSubTab 1");
		etp4.addClick(this, "etp4Clicked");
		etc2.add(etp4);

		ExtTabPage etp5 = new ExtTabPage("ExtSubTab 2");
		etp5.addClick(this, "etp5Clicked");
		etc2.add(etp5);

		label = new Label("No news");
		label.setLocation(80, 360);
		this.add(label);
	}

	public void etp1Clicked() {
		label.setText("ExtTab 1 activated");
	}

	public void etp2Clicked() {
		label.setText("ExtTab 2 activated");
	}

	public void etp3Clicked() {
		label.setText("ExtTab 3 activated");
	}

	public void etp4Clicked() {
		label.setText("ExtSubTab 1 activated");
	}

	public void etp5Clicked() {
		label.setText("ExtSubTab 2 activated");
	}
}
