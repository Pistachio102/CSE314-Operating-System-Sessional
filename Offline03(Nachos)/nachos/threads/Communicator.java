package nachos.threads;

import nachos.machine.Lib;

import java.util.LinkedList;
import java.util.Random;

/**
 * A <i>communicator</i> allows threads to synchronously exchange 32-bit
 * messages. Multiple threads can be waiting to <i>speak</i>,
 * and multiple threads can be waiting to <i>listen</i>. But there should never
 * be a time when both a speaker and a listener are waiting, because the two
 * threads can be paired off at this point.
 */
public class Communicator {
    /**
     * Allocate a new communicator.
     */
    public Communicator() {
    }

    /**
     * Wait for a thread to listen through this communicator, and then transfer
     * <i>word</i> to the listener.
     *
     * <p>
     * Does not return until this thread is paired up with a listening thread.
     * Exactly one listener should receive <i>word</i>.
     *
     * @param	word	the integer to transfer.
     */
    public void speak(int word) {
//        Lib.assertTrue(false);
        sharedLock.acquire(); // acquire the lock so that no speakers or audience can enter

        // We force the speaker to wait until an audience comes.
        waitSpeakers += 1;
        while (!hasActiveAudience || hasActiveSpeaker) {
            speaker.sleep();
        }
        waitSpeakers -= 1;
        hasActiveSpeaker = true;

        this.word = word;
        pair.wake();
        pair.sleep();

        hasActiveSpeaker = false;
        if (waitSpeakers > 0)
            speaker.wake();
        sharedLock.release();
    }

    /**
     * Wait for a thread to speak through this communicator, and then return
     * the <i>word</i> that thread passed to <tt>speak()</tt>.
     *
     * @return	the integer transferred.
     */
    public int listen() {
        sharedLock.acquire(); // acquire the lock so that no speakers or audience can enter

        waitAudiences += 1;
        while (hasActiveAudience) {
            audience.sleep();
        }
        waitAudiences -= 1;
        hasActiveAudience = true;

        speaker.wake();
        pair.sleep(); // The audience is waiting for a speaker to wake it up.
        int ret = word;
        pair.wake();

        hasActiveAudience = false;
        if (waitAudiences > 0) // A new audience may come, wake it up.
            audience.wake();
        sharedLock.release();
        return ret;
    }

    /**
     * + : speakers waiting
     * 0 : free
     * - : audiences waiting
     */

    int word;

    boolean hasActiveSpeaker = false;
    boolean hasActiveAudience = false;
    int waitSpeakers = 0;
    int waitAudiences = 0;

    private Lock sharedLock = new Lock();
    private Condition2 speaker = new Condition2(sharedLock);
    private Condition2 audience = new Condition2(sharedLock);
    private Condition2 pair = new Condition2(sharedLock);
}

