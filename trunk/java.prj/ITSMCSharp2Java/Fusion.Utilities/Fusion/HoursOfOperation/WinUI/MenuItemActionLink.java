package Fusion.HoursOfOperation.WinUI;

import java.awt.MenuItem;

import Fusion.control.EventArgs;
import Fusion.control.IDisposable;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:29
 */
public class MenuItemActionLink extends BasicActionLink implements IDisposable {

	private Boolean m_bIsDisposed = false;
	private Action mAction;
	private MenuItem mClient;

	public MenuItemActionLink(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param action
	 * @param client
	 */
	public MenuItemActionLink(Action action, MenuItem client){

	}

	public void ActionChanged(){

	}

	public void Dispose(){

	}

	/**
	 * 
	 * @param bDisposing
	 */
	protected void Dispose(Boolean bDisposing){

	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	private void OnClientClick(Object sender, EventArgs e){

	}

}