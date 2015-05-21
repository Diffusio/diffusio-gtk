import gtk
import webkit 

view = webkit.WebView() 

sw = gtk.ScrolledWindow() 
sw.add(view) 

win = gtk.Window(gtk.WINDOW_TOPLEVEL) 
win.set_default_size(850,500)
win.add(sw) 
win.show_all() 
view.open("file:///home/pierremtb/diffusio.github.io/templates/material/index.html") 
gtk.main()