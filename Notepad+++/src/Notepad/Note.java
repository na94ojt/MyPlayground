package Notepad;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.text.*;
import java.io.*;
import java.util.*;

public class Note extends JFrame {
  final static int WIDTH = 400;
  final static int HEIGHT = 300;
  StyledDocument doc;
  JTextPane pane;
  JLabel statusInfo;
  JTextArea jTextArea = new JTextArea();

  public Note(String lab) {
    super (lab);

    Container c = getContentPane();

    statusInfo = new JLabel();
    c.add (statusInfo, BorderLayout.SOUTH);

    doc = new DefaultStyledDocument();
    pane = new JTextPane (doc);

    JScrollPane sp = new JScrollPane (pane);
    c.add(sp, BorderLayout.CENTER);

    JMenuBar menuBar = new JMenuBar();
    setJMenuBar (menuBar);
    //�޴�
    JMenu file = new JMenu ("����");
    JMenuItem item;
    file.add (item = new JMenuItem ("������"));
    item.addActionListener (new ActionListener() {
      public void actionPerformed (ActionEvent e) {
        doNewCommand();
      }
    });
    file.add (item = new JMenuItem ("����"));
    item.addActionListener (new ActionListener() {
      public void actionPerformed (ActionEvent e) {
        doOpenCommand();
      }
    });
    file.add (item = new JMenuItem ("�ؽ�Ʈ �ε�"));
    item.addActionListener (new ActionListener() {
      public void actionPerformed (ActionEvent e) {
        doLoadCommand();
      }
    });
    file.add (item = new JMenuItem ("����"));
    item.addActionListener (new ActionListener() {
      public void actionPerformed (ActionEvent e) {
        doSaveCommand();
      }
    });
    file.addSeparator();
    file.add (item = new JMenuItem ("�ݱ�"));
    item.addActionListener (new ActionListener() {
      public void actionPerformed (ActionEvent e) {
        doCloseCommand();
      }
    });
    menuBar.add (file);
    //������
    JMenu color = new JMenu("Color");
    color.add (item = new JMenuItem ("Red"));
    item.setIcon (new ColoredBox(Color.red));
    item.addActionListener (new
      StyledEditorKit.ForegroundAction (
        "set-foreground-red", Color.red));
    color.add (item = new JMenuItem ("Orange"));
    item.setIcon (new ColoredBox(Color.orange));
    item.addActionListener (new
      StyledEditorKit.ForegroundAction (
        "set-foreground-orange", Color.orange));
    color.add (item = new JMenuItem ("Yellow"));
    item.setIcon (new ColoredBox(Color.yellow));
    item.addActionListener (new
      StyledEditorKit.ForegroundAction (
        "set-foreground-yellow", Color.yellow));
    color.add (item = new JMenuItem ("Green"));
    item.setIcon (new ColoredBox(Color.green));
    item.addActionListener (new
      StyledEditorKit.ForegroundAction (
        "set-foreground-green", Color.green));
    color.add (item = new JMenuItem ("Blue"));
    item.setIcon (new ColoredBox(Color.blue));
    item.addActionListener (new
      StyledEditorKit.ForegroundAction (
        "set-foreground-blue", Color.blue));
    color.add (item = new JMenuItem ("Magenta"));
    item.setIcon (new ColoredBox(Color.magenta));
    item.addActionListener (new
      StyledEditorKit.ForegroundAction (
        "set-foreground-magenta", Color.magenta));
    color.add (item = new JMenuItem ("�� ����"));
    item.addActionListener (new ActionListener() {
      public void actionPerformed (ActionEvent e) {
        doColorCommand();
      }
    });

    menuBar.add (color);
    //��Ʈ �޴�
    JMenu font = new JMenu("��Ʈ");
    font.add (item = new JMenuItem ("12"));
    item.addActionListener (new
      StyledEditorKit.FontSizeAction (
        "font-size-12", 12));
    font.add (item = new JMenuItem ("24"));
    item.addActionListener (new
      StyledEditorKit.FontSizeAction (
        "font-size-24", 24));
    font.add (item = new JMenuItem ("36"));
    item.addActionListener (new
      StyledEditorKit.FontSizeAction (
        "font-size-36", 36));
    font.addSeparator();
    font.add (item = new JMenuItem ("����ü"));
    item.setFont (new Font ("Serif", Font.PLAIN, 12));
    item.addActionListener (new
      StyledEditorKit.FontFamilyAction (
        "font-family-Serif", "Serif"));
    font.add (item = new JMenuItem ("���ü"));
    item.setFont (new Font ("SansSerif", Font.PLAIN, 12));
    item.addActionListener (new
      StyledEditorKit.FontFamilyAction (
        "font-family-SansSerif", "SansSerif"));
    font.addSeparator();
    font.add (item = new JMenuItem ("���ϱ�"));
    item.setFont (new Font ("Serif", Font.BOLD, 12));
    item.addActionListener (
      new StyledEditorKit.BoldAction ());
    font.add (item = new JMenuItem ("�����"));
    item.setFont (new Font ("Serif", Font.ITALIC, 12));
    item.addActionListener (
      new StyledEditorKit.ItalicAction ());

    menuBar.add (font);
    //���ԸŴ�
    JMenu insert = new JMenu("����");
    insert.add (item = new JMenuItem ("���� ����"));
    item.addActionListener (new ActionListener() {
      public void actionPerformed (ActionEvent e) {
        doInsertImageCommand();
      }
    });
    menuBar.add (insert);
  }

  public static void main (String args[]) {
	Note frame = new Note("Notepad+++");
    frame.addWindowListener(new WindowAdapter() {
      public void windowClosing(WindowEvent e) {System.exit(0);}
    });
    frame.setSize(WIDTH, HEIGHT);
    frame.setVisible(true);
  }

  public void doNewCommand() {
    pane.setStyledDocument (doc = new DefaultStyledDocument());
  }

  public void doCloseCommand() {
    System.exit (0);
  }

  public void doOpenCommand() {
    try {
      FileInputStream fis = new FileInputStream ("doc.ser");
      ObjectInputStream ois = new ObjectInputStream (fis);
      doc = (StyledDocument)ois.readObject();
      ois.close();
      pane.setStyledDocument (doc);
      validate();
      statusInfo.setText ("�Ҿ���⸦ �����Ͽ����ϴ�..");
    } catch (Exception e) {
      statusInfo.setText ("����");
      e.printStackTrace();
    }
  }

  public void doSaveCommand() {
    try {
      FileOutputStream fos = new FileOutputStream ("doc.ser");
      ObjectOutputStream oos = new ObjectOutputStream (fos);
      oos.writeObject (doc);
      oos.flush();
      oos.close();
      statusInfo.setText ("����Ǿ����ϴ�.");
    } catch (IOException e) {
      statusInfo.setText ("����");
      e.printStackTrace();
    }
  }

  public void doLoadCommand() {
    String msg;
    JFileChooser chooser = new JFileChooser();
    int status = chooser.showOpenDialog(this);
    if (status == JFileChooser.APPROVE_OPTION) {
      char data[];
      final Runnable doWaitCursor = new Runnable() {
        public void run() {
          setCursor (Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
        }
      };
      Thread appThread = new Thread() {
        public void run() {
          try {
             SwingUtilities.invokeAndWait(doWaitCursor);
          } catch (Exception e) {
            e.printStackTrace();
          }
        }
      };
      appThread.start();
      File f = chooser.getSelectedFile();
      try {
        // Clear out current document
        pane.setStyledDocument (doc = new DefaultStyledDocument());
        // Read in text file
        FileReader fin = new FileReader (f);
        BufferedReader br = new BufferedReader (fin);
        char buffer[] = new char[4096];
        int len;
        while ((len = br.read (buffer, 0, buffer.length)) != -1) {
          // Insert into pane
          doc.insertString(doc.getLength(),
            new String (buffer, 0, len), null);
        }
        statusInfo.setText ("�ҷ�����: " + f.getName());
      } catch (BadLocationException exc) {
        statusInfo.setText ("�ҷ����� ����: " + f.getName());
      } catch (FileNotFoundException exc) {
        statusInfo.setText ("������ ã�� ���Ͽ����ϴ�.: " + f.getName());
      } catch (IOException exc) {
        statusInfo.setText ("�б� ���� ���� �߻�: " + f.getName());
      }
      final Runnable undoWaitCursor = new Runnable() {
        public void run() {
        setCursor (Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
        }
      };
      appThread = new Thread() {
        public void run() {
          try {
             SwingUtilities.invokeAndWait(undoWaitCursor);
          } catch (Exception e) {
            e.printStackTrace();
          }
        }
      };
      appThread.start();
    }
  }

  public void doColorCommand() {
    Color color = JColorChooser.showDialog(
      this, "������", Color.cyan);
    if (color != null) {
      MutableAttributeSet attr = new SimpleAttributeSet();
      StyleConstants.setForeground(attr, color);
      pane.setCharacterAttributes(attr, false);
    }
  }

  public void doInsertImageCommand() {
    JFileChooser chooser = new JFileChooser();
    int status = chooser.showOpenDialog(this);
    if (status == JFileChooser.APPROVE_OPTION) {
      File file = chooser.getSelectedFile();
      Icon icon = new ImageIcon (file.getAbsolutePath());
      pane.insertIcon (icon);
    }
  }

  class ColoredBox implements Icon {
    Color color;
    public ColoredBox (Color c) {
      color = c;
    }
    public void paintIcon (Component c, Graphics g, int x, int y) {
      g.setColor(color);
      g.fillRect (x, y, getIconWidth(), getIconHeight());
    }
    public int getIconWidth() {
      return 10;
    }
    public int getIconHeight() {
      return 10;
    }
  }

  public Note() {
    try  {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }

  private void jbInit() throws Exception {
    jTextArea.setText("");
    this.getContentPane().add(jTextArea, BorderLayout.CENTER);
  }
}
