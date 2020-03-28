Imports System.IO.Ports
Imports System
Public Class Form1
    Dim a As Integer = 0
    Dim buff() As Byte
    Dim datarec(8) As String
    Dim recnum As Integer
    Dim arrRD() As RadioButton = {RadioButton1, RadioButton3, RadioButton2, RadioButton4}

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Button1.BackColor = Color.Yellow
    End Sub

    Private Sub Button4_Click(sender As Object, e As EventArgs) Handles Button4.Click
        Button4.BackColor = Color.Yellow
    End Sub
    Private Sub Button6_Click(sender As Object, e As EventArgs) Handles Button6.Click
        Button6.BackColor = Color.Yellow
    End Sub
    Private Sub Button7_Click(sender As Object, e As EventArgs) Handles Button7.Click
        Button7.BackColor = Color.Yellow
    End Sub


    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Timer1.Enabled = True
        Form.CheckForIllegalCrossThreadCalls = False
    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        a += 1
        If a >= 5 Then a = 0
        Label9.Text = "RS232正在等待連線"
        For b = 0 To a
            Label9.Text = Label9.Text + "."
        Next
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        SerialPort1.PortName = TextBox3.Text '設定PortName的值
        SerialPort1.Open() '開啟SerialPort
        Label9.Text = "已連接"
        Timer1.Enabled = False
        Timer2.Enabled = True
    End Sub

    Private Sub SerialPort1_DataReceived(ByVal sender As System.Object, ByVal e As System.IO.Ports.SerialDataReceivedEventArgs) Handles SerialPort1.DataReceived
        Dim a As Integer

        Dim x As String
        x = SerialPort1.ReadChar().ToString()

        If (x = "9") Then
            recnum = 0
        End If
        datarec(recnum) = x
        recnum += 1
        If recnum > 8 Then
            If (SerialPort1.IsOpen) Then
                SerialPort1.Write(Send_Byte.Text)
            End If
            recnum = 0

            RichTextBox1.Text = "接收資料成功!!" & vbNewLine
            For a = 0 To 8
                RichTextBox1.Text = RichTextBox1.Text + datarec(a) + vbNewLine
            Next
            TextBox1.Text = datarec(2)
            TextBox2.Text = datarec(3)
            Dim c As Integer = Val(datarec(2))
            Select Case c
                Case 1
                    RadioButton1.Checked = True
                Case 2
                    RadioButton3.Checked = True
                Case 3
                    RadioButton2.Checked = True
                Case 4
                    RadioButton4.Checked = True
            End Select
            If datarec(4) = 1 Then
                Button1.BackColor = Color.Red

            Else
                Button1.BackColor = Color.White
            End If
            If datarec(5) = 1 Then
                Button4.BackColor = Color.Red

            Else
                Button4.BackColor = Color.White
            End If
            If datarec(6) = 1 Then
                Button6.BackColor = Color.Red

            Else
                Button6.BackColor = Color.White
            End If
            If datarec(7) = 1 Then
                Button7.BackColor = Color.Red

            Else
                Button7.BackColor = Color.White
            End If
            If (datarec(2) = datarec(3)) Then
                Label3.Text = "STOP"
            ElseIf datarec(1) = 2 Then
                Label3.Text = "↑"
            Else
                Label3.Text = "↓"

            End If
        End If


    End Sub

    Private Sub Button8_Click(sender As Object, e As EventArgs) Handles Button8.Click
        If (SerialPort1.IsOpen) Then
            SerialPort1.Write(Send_Byte.Text)
        End If

    End Sub

    Private Sub RichTextBox1_TextChanged(sender As Object, e As EventArgs) Handles RichTextBox1.TextChanged

    End Sub

    Private Sub Timer2_Tick(sender As Object, e As EventArgs) Handles Timer2.Tick
        SerialPort1.Write(1)
    End Sub
End Class
