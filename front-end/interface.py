import ctypes
import customtkinter as ctk

backend1 = ctypes.CDLL("./back-end/code.so")
backend2 = ctypes.CDLL("./back-end/telaAluno.so")
backend3 = ctypes.CDLL("./back-end/telaProfessor.so")

ctk.set_appearance_mode("light")
ctk.set_default_color_theme("blue")
interface = ctk.CTk()