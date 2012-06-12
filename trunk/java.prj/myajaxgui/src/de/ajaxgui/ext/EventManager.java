package de.ajaxgui.ext;

import java.util.ArrayList;

import de.ajaxgui.AbstractButton;
import de.ajaxgui.Application;
import de.ajaxgui.CheckBox;
import de.ajaxgui.ComboBox;
import de.ajaxgui.ComboBoxItem;
import de.ajaxgui.DatePicker;
import de.ajaxgui.ListView;
import de.ajaxgui.TextField;
import de.ajaxgui.Tree;
import de.ajaxgui.TreeFile;
import de.ajaxgui.TreeFolder;

public class EventManager {
	private static final ThreadLocal<EventManager> eventManager = new ThreadLocal<EventManager>();

	public static EventManager get() {
		return eventManager.get();
	}

	public static void set(EventManager em) {
		eventManager.set(em);
	}

	private ArrayList<Event> events = new ArrayList<Event>();

	public void addEvent(Event event) {
		events.add(event);
	}

	public ArrayList<Event> getEvents() {
		return events;
	}

	public boolean processEvents() {
		boolean close = false;
		while (true) {
			if (events.size() == 0)
				break;
			Event event = events.get(0);
			if (event.getType() == Event.Type.CLOSE) {
				events.remove(event);
				close = true;
			} else if (event.getType() == Event.Type.CLICK) {
				events.remove(event);
				doClick(event);
			} else if (event.getType() == Event.Type.CHECKEDCHANGED) {
				events.remove(event);
				doCheckedChanged(event);
			} else if (event.getType() == Event.Type.SELECTIONCHANGED) {
				events.remove(event);
				doSelectionChanged(event);
			} else if (event.getType() == Event.Type.TEXTCHANGED) {
				events.remove(event);
				doTextChanged(event);
			} else if (event.getType() == Event.Type.LISTVIEWSELECTIONCHANGED) {
				events.remove(event);
				doListViewSelectionChanged(event);
			} else if (event.getType() == Event.Type.TREESELECTIONCHANGED) {
				events.remove(event);
				doTreeSelectionChanged(event);
			} else if (event.getType() == Event.Type.DATECHANGED) {
				events.remove(event);
				doDateChanged(event);
			} else
				events.remove(event);
		}
		if (close)
			return false;
		Thread servletThread = ThreadManager.get().getServletThread();
		Thread appThread = ThreadManager.get().getApplicationThread();
		while (servletThread.getState() != Thread.State.WAITING) {
		}
		synchronized (servletThread) {
			servletThread.notify();
		}
		try {
			synchronized (appThread) {
				appThread.wait();
			}
			Application app = (Application) appThread;
			app.init();
		} catch (InterruptedException e) {
			return false;
		}
		return true;
	}

	private void doDateChanged(Event event) {
		Component component = ComponentManager.get().getComponent(
				event.getComponentId());
		if (component instanceof DatePicker) {
			DatePicker dtp = (DatePicker) component;
			dtp.date = (String) event.getData();
			dtp.doDateChanged();
		}
	}

	private void doListViewSelectionChanged(Event event) {
		Component component = ComponentManager.get().getComponent(
				event.getComponentId());
		if (component instanceof ListView) {
			ListView lv = (ListView) component;
			lv.selected = lv.listViewItems.get((Integer) event.getData());
			lv.doSelectionChanged();
		}
	}

	private void doTreeSelectionChanged(Event event) {
		Component component = ComponentManager.get().getComponent(
				event.getComponentId());
		if (component instanceof Tree) {
			Tree t = (Tree) component;
			t.doSelectionChanged(component);
		}if (component instanceof TreeFolder) {
			Tree t = getTree((TreeFolder) component);
			t.doSelectionChanged(component);
		}if (component instanceof TreeFile) {
			Tree t = getTree((TreeFolder)((TreeFile) component).getParent());
			t.doSelectionChanged(component);
		}
	}

	private Tree getTree(TreeFolder t){
		if (t.getParent() == null) return null;
		if (t.getParent() instanceof TreeFolder) return getTree((TreeFolder)t.getParent());
		if (t.getParent() instanceof Tree) return (Tree)t.getParent();
		return null;
	}
	
	private void doTextChanged(Event event) {
		Component component = ComponentManager.get().getComponent(
				event.getComponentId());
		if (component instanceof TextField) {
			TextField tf = (TextField) component;
			tf.text = (String) event.getData();
			tf.doTextChanged();
		}
	}

	private void doSelectionChanged(Event event) {
		Component component = ComponentManager.get().getComponent(
				event.getComponentId());
		if (component instanceof ComboBox) {
			ComboBox cb = (ComboBox) component;
			cb.selected = (ComboBoxItem) ComponentManager.get().getComponent(
					(Integer) event.getData());
			cb.doSelectionChanged();
		}
	}

	private void doCheckedChanged(Event event) {
		Component component = ComponentManager.get().getComponent(
				event.getComponentId());
		if (component instanceof CheckBox) {
			CheckBox cb = (CheckBox) component;
			cb.checked = (Boolean) event.getData();
			cb.doCheckedChanged();
		}
	}

	private void doClick(Event event) {
		Component component = ComponentManager.get().getComponent(
				event.getComponentId());
		// if (component instanceof TabPage) {
		// TabPage tp = (TabPage) component;
		// tp.control.selected = tp;
		// tp.doClick();
		// } else
		if (component instanceof AbstractButton) {
			AbstractButton button = (AbstractButton) component;
			button.doClick();
		}
	}
}
