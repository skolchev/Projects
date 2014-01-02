<%@ Page Title="CreatePost" Language="C#" MasterPageFile="~/Site.Master" 
    AutoEventWireup="true" CodeBehind="CreatePost.aspx.cs" 
    Inherits="SapphireForum.Application.CreatePost" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">

    <h2>Create new post</h2>
    <asp:Label runat="server" AssociatedControlID="PostTitleTextBox" Text="Choose Category: " />
    <asp:DropDownList ID="CategoriesDropDownList" runat="server" SelectMethod="CategoriesDropList_GetData" ></asp:DropDownList>
    <asp:Label runat="server" AssociatedControlID="PostTitleTextBox" Text="Title: " />
    <asp:TextBox ID="PostTitleTextBox" runat="server" Width="400px" />
    <asp:Label runat="server" AssociatedControlID="PostTextTextBox" Text="Text: " />
    <asp:TextBox ID="PostTextTextBox" runat="server" TextMode="MultiLine" Height="100px" Width="400px" />
    <asp:Label runat="server" AssociatedControlID="PostTagsTextBox" Text="Tags(separated by single space): " />
    <asp:TextBox ID="PostTagsTextBox" runat="server" Width="400px" />
    <br />
    <asp:LinkButton ID="CreatePostLinkButton" runat="server" 
        Text="Create Post" OnClick="CreatePostLinkButton_Click"/>

</asp:Content>
