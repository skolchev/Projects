<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Users.aspx.cs" Inherits="SapphireForum.Application.Users" %>
<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <h3>Most active users</h3>    
    <asp:Repeater ID="RepeaterUserTemplate" runat="server"
        ItemType="SapphireForum.Application.Models.ApplicationUser"
        SelectMethod="RepeaterUserTemplate_GetData">
        <HeaderTemplate>
            <table class="top-users-table">
        </HeaderTemplate>
        <ItemTemplate>
            <tr>
                <td class="top-users-data">
                    <img src="<%#: Item.AvatarLink %>" width="30" height="30" class="img-rounded"/>
                    <span class="top-users-name"><%#: Item.UserName %></span>
                </td>
                <td class="top-users-posts-count">
                    <asp:LinkButton runat="server" ID="LinkButtonPosts"
                         OnCommand="RedirectToPosts_Click" CommandArgument="<%#: Item.UserName %>">
                        Posts: <%#: Item.Posts.Count %>
                    </asp:LinkButton>
                </td>
            </tr>
        </ItemTemplate>
        <FooterTemplate>
            </table>
        </FooterTemplate>
    </asp:Repeater>
</asp:Content>