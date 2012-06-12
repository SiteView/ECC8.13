/*
 * Created on 2005-2-9 3:06:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Utils;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

public class NullSecurityManager extends SecurityManager {

    public void checkPermission(java.security.Permission permission, Object obj) {
    }

    public void checkRead(String s, Object obj) {
    }

    public void checkConnect(String s, int i, Object obj) {
    }

    public void checkPermission(java.security.Permission permission) {
    }

    public void checkMulticast(java.net.InetAddress inetaddress) {
    }

    public void checkAccess(ThreadGroup threadgroup) {
    }

    public void checkConnect(String s, int i) {
    }

    public void checkAccess(Thread thread) {
    }

    public NullSecurityManager() {
    }

    public void checkAwtEventQueueAccess() {
    }

    public void checkCreateClassLoader() {
    }

    public void checkPrintJobAccess() {
    }

    public void checkPropertiesAccess() {
    }

    public void checkSetFactory() {
    }

    public void checkSystemClipboardAccess() {
    }

    public void checkExit(int i) {
    }

    public void checkListen(int i) {
    }

    public void checkRead(java.io.FileDescriptor filedescriptor) {
    }

    public void checkWrite(java.io.FileDescriptor filedescriptor) {
    }

    public void checkMemberAccess(Class class1, int i) {
    }

    public boolean checkTopLevelWindow(Object obj) {
        return true;
    }

    public void checkDelete(String s) {
    }

    public void checkExec(String s) {
    }

    public void checkLink(String s) {
    }

    public void checkPackageAccess(String s) {
    }

    public void checkPackageDefinition(String s) {
    }

    public void checkPropertyAccess(String s) {
    }

    public void checkRead(String s) {
    }

    public void checkSecurityAccess(String s) {
    }

    public void checkWrite(String s) {
    }

    public void checkAccept(String s, int i) {
    }
}
