<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Post.aspx.cs" Inherits="SapphireForum.Application.Admin.Post" %>

<asp:Content ID="ContentAdminPosts" ContentPlaceHolderID="MainContent" runat="server">
    <div class="row">
        <div class="span12">
            <div class="control-group">
                <asp:Label CssClass="control-label" AssociatedControlID="TextBoxTitle" runat="server">Title</asp:Label>
                <div class="controls">
                    <asp:TextBox ID="TextBoxTitle" runat="server"></asp:TextBox>
                </div>
            </div>
            <div class="control-group">
                <asp:Label CssClass="control-label" AssociatedControlID="TextBoxText" runat="server">Text</asp:Label>
                <div class="controls">
                    <asp:TextBox ID="TextBoxText" runat="server" TextMode="MultiLine"></asp:TextBox>
                </div>
            </div>
            <asp:HiddenField ID="HiddenFieldPostDate" runat="server"></asp:HiddenField>
            <div class="control-group">
                <asp:Label CssClass="control-label" AssociatedControlID="TextBoxTags" runat="server">Tags</asp:Label>
                <div class="controls">
                    <asp:TextBox ID="TextBoxTags" runat="server"></asp:TextBox>
                </div>
            </div>
            <div class="control-group">
                <asp:Label CssClass="control-label" AssociatedControlID="TextBoxTitle" runat="server">Categories</asp:Label>
                <div class="controls">
                    <asp:DropDownList ID="DropDownCategories" runat="server">
                        <asp:ListItem Text="(no supplier)" Value="" />
                    </asp:DropDownList>
                </div>
            </div>
            <asp:Button runat="server" CssClass="btn btn-primary" Text="Edit" OnClick="EditPost_Click" />
        </div>
    </div>
</asp:Content>
