package de.ajaxgui.test;

import de.ajaxgui.Label;
import de.ajaxgui.Tree;
import de.ajaxgui.TreeFolder;
import de.ajaxgui.TreeFile;
import de.ajaxgui.MainForm;
import de.ajaxgui.ext.Component;

public class TreeMainForm extends MainForm {
	private Label label = null;

	public TreeMainForm() {
		Tree t = new Tree("Root");
		t.setBackgroundColor(255);
		t.setOverflow("scrollY");
		//tree.setHeight(null);
		t.setTop(48);
		t.setLeft(20);
		t.setWidth(200);
		t.setBottom(48);
		this.add(t);
		
		TreeFolder te1 = new TreeFolder("Desktop", "icons/16/desktop.png", "icons/16/dictionary.png");
	      t.add(te1);

	      TreeFolder te1_1 = new TreeFolder("Files");
	      TreeFolder te1_2 = new TreeFolder("Workspace");
	      TreeFolder te1_3 = new TreeFolder("Network");
	      TreeFolder te1_4 = new TreeFolder("Trash");

	      te1.add(te1_1, te1_2, te1_3, te1_4);
	      
	      TreeFile te1_2_1 = new TreeFile("Windows (C:)", "icons/16/harddrive.png");
	      TreeFile te1_2_2 = new TreeFile("Documents (D:)", "icons/16/harddrive.png");

	      te1_2.add(te1_2_1, te1_2_2);
	      
	      TreeFolder te2_8 = new TreeFolder("Big");
	      
	      for (int i=0;i<50; i++) {
	        te2_8.add(new TreeFolder("Item " + i));
	      };
	      
	      te1.add(te2_8);
	      t.addSelectionChanged(this, "treeSelectionChanged");
			label = new Label("No news");
			label.setTop(80);
			label.setLeft(250);
			this.add(label);
	}
	public void treeSelectionChanged(Component component) {
		if (component instanceof Tree) {
			Tree t = (Tree) component;
			label.setText(t.getText());
		}if (component instanceof TreeFolder) {
			TreeFolder t = (TreeFolder) component;
			label.setText(t.getText());
		}if (component instanceof TreeFile) {
			TreeFile t = (TreeFile) component;
			label.setText(t.getText());
		}
	}
	
}
