Imports System.IO.Ports

Public Class Form1
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        System.Windows.Forms.Control.CheckForIllegalCrossThreadCalls = False 'ทำให้เชื่อมต่ออุปกรณ์ภายนอกได้
        Button1.BackColor = Color.Black 'เริ่มโปรแกรมวงกลมเป็นสีดำ
        Button2.BackColor = Color.Black 'เริ่มโปรแกรมวงกลมเป็นสีดำ
        SerialPort1.Open() 'เริ่มโปรแกรมสามารถใช้งาน Portได้เลย
    End Sub

    Private Sub SerialPort1_DataReceived(sender As Object, e As SerialDataReceivedEventArgs) Handles SerialPort1.DataReceived
        Dim line As String = SerialPort1.ReadLine()
        Dim node As String = line.Substring(0, 2)
        If node = "X1" Then
            Dim head As String = line.Substring(2, 1)
            If head = "L" Then
                Dim ledState As String = line.Substring(3, 1)
                If ledState = "1" Then
                    Button1.BackColor = Color.Red
                Else
                    Button1.BackColor = Color.Black
                End If
            End If
            If head = "V" Then
                Dim Voltage As String = line.Substring(3, 4)
                Label2.Text = Voltage + " V"
            End If
        End If
        If node = "X2" Then
            Dim head As String = line.Substring(2, 1)
            If head = "L" Then
                Dim ledState As String = line.Substring(3, 1)
                If ledState = "1" Then
                    Button2.BackColor = Color.Red
                Else
                    Button2.BackColor = Color.Black
                End If
            End If
            If head = "V" Then
                Dim Voltage As String = line.Substring(3, 4)
                Label3.Text = Voltage + " V"
            End If
        End If

    End Sub

    Private Sub Label2_Click(sender As Object, e As EventArgs) Handles Label2.Click

    End Sub

    Private Sub Label1_Click(sender As Object, e As EventArgs) Handles Label1.Click

    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        Button1.BackColor = Color.Red
        SerialPort1.Write("X1L1")
    End Sub

    Private Sub Button4_Click(sender As Object, e As EventArgs) Handles Button4.Click
        Button1.BackColor = Color.Black
        SerialPort1.Write("X1L0")
    End Sub

    Private Sub Button5_Click(sender As Object, e As EventArgs) Handles Button5.Click
        SerialPort1.Write("X1V")
    End Sub

    Private Sub Button8_Click(sender As Object, e As EventArgs) Handles Button8.Click
        Button2.BackColor = Color.Red
        SerialPort1.Write("X2L1")
    End Sub

    Private Sub Button7_Click(sender As Object, e As EventArgs) Handles Button7.Click
        Button2.BackColor = Color.Black
        SerialPort1.Write("X2L0")
    End Sub

    Private Sub Button6_Click(sender As Object, e As EventArgs) Handles Button6.Click
        SerialPort1.Write("X2V")
    End Sub

    Private Sub Label3_Click(sender As Object, e As EventArgs) Handles Label3.Click

    End Sub
End Class
