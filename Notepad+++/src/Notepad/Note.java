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
    //메뉴
    JMenu file = new JMenu ("파일");
    JMenuItem item;
    file.add (item = new JMenuItem ("새파일"));
    item.addActionListener (new ActionListener() {
      public void actionPerformed (ActionEvent e) {
        doNewCommand();
      }
    });
    file.add (item = new JMenuItem ("열기"));
    item.addActionListener (new ActionListener() {
      public void actionPerformed (ActionEvent e) {
        doOpenCommand();
      }
    });
    file.add (item = new JMenuItem ("텍스트 로드"));
    item.addActionListener (new ActionListener() {
      public void actionPerformed (ActionEvent e) {
        doLoadCommand();
      }
    });
    file.add (item = new JMenuItem ("저장"));
    item.addActionListener (new ActionListener() {
      public void actionPerformed (ActionEvent e) {
        doSaveCommand();
      }
    });
    file.addSeparator();
    file.add (item = new JMenuItem ("닫기"));
    item.addActionListener (new ActionListener() {
      public void actionPerformed (ActionEvent e) {
        doCloseCommand();
      }
    });
    menuBar.add (file);
    //색지정
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
    color.add (item = new JMenuItem ("색 지정"));
    item.addActionListener (new ActionListener() {
      public void actionPerformed (ActionEvent e) {
        doColorCommand();
      }
    });

    menuBar.add (color);
    //폰트 메뉴
    JMenu font = new JMenu("폰트");
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
    font.add (item = new JMenuItem ("명조체"));
    item.setFont (new Font ("Serif", Font.PLAIN, 12));
    item.addActionListener (new
      StyledEditorKit.FontFamilyAction (
        "font-family-Serif", "Serif"));
    font.add (item = new JMenuItem ("고딕체"));
    item.setFont (new Font ("SansSerif", Font.PLAIN, 12));
    item.addActionListener (new
      StyledEditorKit.FontFamilyAction (
        "font-family-SansSerif", "SansSerif"));
    font.addSeparator();
    font.add (item = new JMenuItem ("진하기"));
    item.setFont (new Font ("Serif", Font.BOLD, 12));
    item.addActionListener (
      new StyledEditorKit.BoldAction ());
    font.add (item = new JMenuItem ("기울임"));
    item.setFont (new Font ("Serif", Font.ITALIC, 12));
    item.addActionListener (
      new StyledEditorKit.ItalicAction ());

    menuBar.add (font);
    //사입매뉴
    JMenu insert = new JMenu("삽입");
    insert.add (item = new JMenuItem ("파일 삽입"));
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
      statusInfo.setText ("불어오기를 성공하였습니다..");
    } catch (Exception e) {
      statusInfo.setText ("에러");
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
      statusInfo.setText ("저장되었습니다.");
    } catch (IOException e) {
      statusInfo.setText ("에러");
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
        statusInfo.setText ("불러오기: " + f.getName());
      } catch (BadLocationException exc) {
        statusInfo.setText ("불러오기 실패: " + f.getName());
      } catch (FileNotFoundException exc) {
        statusInfo.setText ("파일을 찾지 못하였습니다.: " + f.getName());
      } catch (IOException exc) {
        statusInfo.setText ("읽기 쓰기 오류 발생: " + f.getName());
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
      this, "색선택", Color.cyan);
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
