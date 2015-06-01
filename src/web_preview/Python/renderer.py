import gtk
import webkit 

view = webkit.WebView() 
sw = gtk.ScrolledWindow() 
sw.add(view)
win = gtk.Window(gtk.WIN_POS_MOUSE) 
win.set_default_size(850,600)
win.add(sw)
win.set_title("DiffusioRenderer")
win.show_all() 
view.open("file:///home/pierremtb/diffusio.github.io/templates/material/index.html") 


class Tools(gtk.Window):
    def __init__(self):
        super(Tools, self).__init__()
        
        self.set_title("DR Tools")
        self.set_size_request(150, 55)
        self.set_resizable(False)
        self.set_position(gtk.WINDOW_TOPLEVEL)
        self.connect("destroy", self.on_destroy)
        
        fixed = gtk.Fixed()

        refresh = gtk.Button("Refresh")
        refresh.connect("clicked", self.on_clicked)
        refresh.set_size_request(120, 35)

        fixed.put(refresh, 15, 10)

        self.add(fixed)
        self.show_all()
        
    def on_destroy(self, widget):
        gtk.main_quit()
        
    def on_clicked(self, widget):
        view.reload()


Tools()
gtk.main()